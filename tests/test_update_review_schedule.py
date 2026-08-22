from __future__ import annotations

import importlib.util
import csv
import subprocess
import sys
import tempfile
import unittest
from datetime import date, datetime
from pathlib import Path


SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "update_review_schedule.py"
SPEC = importlib.util.spec_from_file_location("update_review_schedule", SCRIPT)
assert SPEC and SPEC.loader
scheduler = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = scheduler
SPEC.loader.exec_module(scheduler)


def commit(repo: Path, message: str, timestamp: str, *files: str) -> None:
    subprocess.run(["git", "add", *files], cwd=repo, check=True, capture_output=True)
    env = {
        "GIT_AUTHOR_DATE": timestamp,
        "GIT_COMMITTER_DATE": timestamp,
    }
    subprocess.run(
        ["git", "commit", "-m", message],
        cwd=repo,
        check=True,
        capture_output=True,
        env={**__import__("os").environ, **env},
    )


class SchedulerTests(unittest.TestCase):
    def setUp(self) -> None:
        self.temp = tempfile.TemporaryDirectory()
        self.repo = Path(self.temp.name)
        subprocess.run(["git", "init", "-q"], cwd=self.repo, check=True)
        subprocess.run(["git", "config", "user.name", "Test User"], cwd=self.repo, check=True)
        subprocess.run(["git", "config", "user.email", "test@example.com"], cwd=self.repo, check=True)

    def tearDown(self) -> None:
        self.temp.cleanup()

    def write(self, path: str, content: str = "solution") -> None:
        target = self.repo / path
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(content, encoding="utf-8")

    def test_inventory_groups_languages_and_excludes_nested_files(self) -> None:
        self.write("two-sum.cpp")
        self.write("two-sum.py")
        self.write("incorrect/two-sum.cpp")
        commit(self.repo, "solve", "2026-08-10T10:00:00+02:00", "two-sum.cpp", "two-sum.py", "incorrect/two-sum.cpp")
        grouped = scheduler.tracked_problem_files(self.repo)
        self.assertEqual(grouped, {"two-sum": ("two-sum.cpp", "two-sum.py")})

    def test_new_implementation_is_due_in_two_days(self) -> None:
        history = scheduler.ProblemHistory(
            "Two Sum",
            ("two-sum.cpp",),
            datetime.fromisoformat("2026-08-10T10:00:00+02:00"),
            datetime.fromisoformat("2026-08-10T10:00:00+02:00"),
            1,
        )
        row = scheduler.build_row(history, [], date(2026, 8, 16))
        self.assertEqual(row["due_date"], "2026-08-12")
        self.assertEqual(row["overdue_days"], 4)

    def test_adaptive_intervals_and_reset(self) -> None:
        history = scheduler.ProblemHistory(
            "Two Sum",
            ("two-sum.cpp",),
            datetime.fromisoformat("2026-08-01T10:00:00+02:00"),
            datetime.fromisoformat("2026-08-01T10:00:00+02:00"),
            1,
        )

        def review(day: int, result: str) -> object:
            return scheduler.Review(
                datetime.fromisoformat(f"2026-08-{day:02d}T10:00:00+02:00"),
                "Two Sum",
                result,
                "transition" if result != "pass" else "",
                "10",
                "0",
                "",
            )

        first_pass = scheduler.build_row(history, [review(3, "pass")], date(2026, 8, 3))
        self.assertEqual((first_pass["interval_days"], first_pass["due_date"]), (7, "2026-08-10"))
        second_pass = scheduler.build_row(history, [review(3, "pass"), review(10, "pass")], date(2026, 8, 10))
        self.assertEqual((second_pass["interval_days"], second_pass["due_date"]), (21, "2026-08-31"))
        failed = scheduler.build_row(history, [review(3, "pass"), review(10, "fail")], date(2026, 8, 10))
        self.assertEqual((failed["consecutive_passes"], failed["interval_days"], failed["due_date"]), (0, 1, "2026-08-11"))
        partial = scheduler.build_row(history, [review(12, "partial")], date(2026, 8, 12))
        self.assertEqual((partial["interval_days"], partial["due_date"]), (3, "2026-08-15"))

    def test_later_implementation_resets_review_progress(self) -> None:
        history = scheduler.ProblemHistory(
            "Two Sum",
            ("two-sum.cpp",),
            datetime.fromisoformat("2026-08-01T10:00:00+02:00"),
            datetime.fromisoformat("2026-08-10T10:00:00+02:00"),
            2,
        )
        old_review = scheduler.Review(
            datetime.fromisoformat("2026-08-05T10:00:00+02:00"),
            "Two Sum",
            "pass",
            "",
            "8",
            "0",
            "",
        )
        row = scheduler.build_row(history, [old_review], date(2026, 8, 10))
        self.assertEqual(row["due_date"], "2026-08-12")
        self.assertEqual(row["consecutive_passes"], 0)
        self.assertEqual(row["last_result"], "")

    def test_activity_ignores_nested_and_documentation_commits(self) -> None:
        self.write("README.md")
        commit(self.repo, "docs", "2026-08-10T10:00:00+02:00", "README.md")
        self.assertFalse(scheduler.has_activity(self.repo, date(2026, 8, 10)))
        self.write("problem.cpp")
        commit(self.repo, "solve", "2026-08-11T10:00:00+02:00", "problem.cpp")
        self.assertTrue(scheduler.has_activity(self.repo, date(2026, 8, 11)))

    def test_hinted_pass_is_rejected(self) -> None:
        self.write("two-sum.cpp")
        commit(self.repo, "solve", "2026-08-10T10:00:00+02:00", "two-sum.cpp")
        log = self.repo / "mindsolve-log.csv"
        with log.open("w", newline="", encoding="utf-8") as handle:
            writer = csv.DictWriter(handle, fieldnames=scheduler.LOG_FIELDS)
            writer.writeheader()
            writer.writerow(
                {
                    "reviewed_at": "2026-08-12T10:00:00+02:00",
                    "problem": "Two Sum",
                    "result": "pass",
                    "failure_stage": "",
                    "elapsed_minutes": "8",
                    "hints": "1",
                    "notes": "",
                }
            )
        histories = scheduler.load_histories(self.repo)
        with self.assertRaisesRegex(scheduler.ScheduleError, "hinted review"):
            scheduler.parse_reviews(log, histories)


if __name__ == "__main__":
    unittest.main()
