#!/usr/bin/env python3
"""Generate a mindsolve review schedule from Git history and review events."""

from __future__ import annotations

import argparse
import csv
import os
import subprocess
import sys
import tempfile
from collections import defaultdict
from dataclasses import dataclass
from datetime import date, datetime, time, timedelta
from pathlib import Path
from zoneinfo import ZoneInfo


TIMEZONE = ZoneInfo("Europe/Paris")
SOURCE_SUFFIXES = {".cpp", ".py", ".cu", ".slang"}
VALID_RESULTS = {"pass", "partial", "fail"}
LOG_FIELDS = (
    "reviewed_at",
    "problem",
    "result",
    "failure_stage",
    "elapsed_minutes",
    "hints",
    "notes",
)
OUTPUT_FIELDS = (
    "due_date",
    "problem",
    "file",
    "first_solved",
    "last_implemented",
    "attempts",
    "last_mindsolve",
    "last_result",
    "consecutive_passes",
    "interval_days",
    "overdue_days",
    "failure_stage",
)


class ScheduleError(ValueError):
    pass


@dataclass(frozen=True)
class Review:
    reviewed_at: datetime
    problem: str
    result: str
    failure_stage: str
    elapsed_minutes: str
    hints: str
    notes: str


@dataclass(frozen=True)
class ProblemHistory:
    problem: str
    files: tuple[str, ...]
    first_implemented: datetime
    last_implemented: datetime
    attempts: int


def run_git(repo: Path, *args: str) -> str:
    process = subprocess.run(
        ["git", *args],
        cwd=repo,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    if process.returncode != 0:
        raise ScheduleError(process.stderr.strip() or "git command failed")
    return process.stdout


def tracked_problem_files(repo: Path) -> dict[str, tuple[str, ...]]:
    output = run_git(repo, "ls-files")
    grouped: dict[str, list[str]] = defaultdict(list)
    for raw in output.splitlines():
        path = Path(raw)
        if path.parent != Path(".") or path.suffix.lower() not in SOURCE_SUFFIXES:
            continue
        grouped[path.stem.casefold()].append(path.as_posix())
    return {stem: tuple(sorted(files)) for stem, files in grouped.items()}


SPECIAL_WORDS = {
    "ii": "II",
    "iii": "III",
    "iv": "IV",
    "bfs": "BFS",
    "dfs": "DFS",
    "bst": "BST",
    "dsa": "DSA",
    "lru": "LRU",
    "kth": "Kth",
    "3sum": "3Sum",
    "2sum": "2Sum",
}


def display_name(stem: str) -> str:
    words = stem.replace("_", "-").split("-")
    return " ".join(SPECIAL_WORDS.get(word.casefold(), word.capitalize()) for word in words)


def parse_git_datetime(value: str) -> datetime:
    return datetime.fromisoformat(value).astimezone(TIMEZONE)


def history_for_problem(repo: Path, stem: str, files: tuple[str, ...]) -> ProblemHistory:
    output = run_git(repo, "log", "--format=%H%x09%cI", "--", *files)
    commits: dict[str, datetime] = {}
    for line in output.splitlines():
        if not line:
            continue
        sha, timestamp = line.split("\t", 1)
        commits[sha] = parse_git_datetime(timestamp)
    if not commits:
        raise ScheduleError(f"tracked problem has no Git history: {', '.join(files)}")
    timestamps = tuple(commits.values())
    return ProblemHistory(
        problem=display_name(stem),
        files=files,
        first_implemented=min(timestamps),
        last_implemented=max(timestamps),
        attempts=len(commits),
    )


def load_histories(repo: Path) -> list[ProblemHistory]:
    return [
        history_for_problem(repo, stem, files)
        for stem, files in sorted(tracked_problem_files(repo).items())
    ]


def normalize_problem(value: str) -> str:
    return " ".join(value.casefold().replace("_", " ").replace("-", " ").split())


def parse_reviews(path: Path, histories: list[ProblemHistory]) -> list[Review]:
    if not path.exists():
        raise ScheduleError(f"missing mindsolve log: {path}")

    aliases: dict[str, str] = {}
    for history in histories:
        keys = {history.problem, *(Path(file).stem for file in history.files)}
        for key in keys:
            normalized = normalize_problem(key)
            if normalized in aliases and aliases[normalized] != history.problem:
                raise ScheduleError(f"ambiguous problem alias: {key}")
            aliases[normalized] = history.problem

    reviews: list[Review] = []
    seen: set[tuple[str, datetime]] = set()
    with path.open(newline="", encoding="utf-8") as handle:
        reader = csv.DictReader(handle)
        if tuple(reader.fieldnames or ()) != LOG_FIELDS:
            raise ScheduleError(
                f"mindsolve log header must be exactly: {','.join(LOG_FIELDS)}"
            )
        for row_number, row in enumerate(reader, start=2):
            raw_problem = row["problem"].strip()
            canonical = aliases.get(normalize_problem(raw_problem))
            if not canonical:
                raise ScheduleError(f"row {row_number}: unknown problem {raw_problem!r}")
            result = row["result"].strip().casefold()
            if result not in VALID_RESULTS:
                raise ScheduleError(f"row {row_number}: invalid result {result!r}")
            try:
                reviewed_at = datetime.fromisoformat(row["reviewed_at"].strip())
            except ValueError as error:
                raise ScheduleError(f"row {row_number}: invalid reviewed_at") from error
            if reviewed_at.tzinfo is None:
                raise ScheduleError(f"row {row_number}: reviewed_at must include a timezone")
            reviewed_at = reviewed_at.astimezone(TIMEZONE)
            elapsed_minutes = row["elapsed_minutes"].strip()
            hints = row["hints"].strip()
            try:
                if elapsed_minutes and int(elapsed_minutes) < 0:
                    raise ValueError
            except ValueError as error:
                raise ScheduleError(
                    f"row {row_number}: elapsed_minutes must be a non-negative integer"
                ) from error
            try:
                hint_count = int(hints or "0")
                if hint_count < 0:
                    raise ValueError
            except ValueError as error:
                raise ScheduleError(
                    f"row {row_number}: hints must be a non-negative integer"
                ) from error
            if result == "pass" and hint_count:
                raise ScheduleError(
                    f"row {row_number}: a hinted review must be partial or fail"
                )
            event_key = (canonical, reviewed_at)
            if event_key in seen:
                raise ScheduleError(f"row {row_number}: duplicate review event")
            seen.add(event_key)
            reviews.append(
                Review(
                    reviewed_at=reviewed_at,
                    problem=canonical,
                    result=result,
                    failure_stage=row["failure_stage"].strip(),
                    elapsed_minutes=elapsed_minutes,
                    hints=str(hint_count),
                    notes=row["notes"].strip(),
                )
            )
    return sorted(reviews, key=lambda review: review.reviewed_at)


def interval_for(result: str, consecutive_passes: int) -> int:
    if result == "fail":
        return 1
    if result == "partial":
        return 3
    if consecutive_passes == 1:
        return 7
    if consecutive_passes == 2:
        return 21
    return 60


def build_row(history: ProblemHistory, reviews: list[Review], today: date) -> dict[str, str | int]:
    all_reviews = sorted(reviews, key=lambda review: review.reviewed_at)
    current_reviews = [
        review for review in all_reviews if review.reviewed_at > history.last_implemented
    ]
    consecutive_passes = 0
    for review in current_reviews:
        consecutive_passes = consecutive_passes + 1 if review.result == "pass" else 0

    latest_any = all_reviews[-1] if all_reviews else None
    if current_reviews:
        latest = current_reviews[-1]
        interval = interval_for(latest.result, consecutive_passes)
        due = latest.reviewed_at.date() + timedelta(days=interval)
        last_result = latest.result
        failure_stage = latest.failure_stage
    else:
        interval = 2
        due = history.last_implemented.date() + timedelta(days=interval)
        last_result = ""
        failure_stage = ""

    return {
        "due_date": due.isoformat(),
        "problem": history.problem,
        "file": ", ".join(history.files),
        "first_solved": history.first_implemented.date().isoformat(),
        "last_implemented": history.last_implemented.date().isoformat(),
        "attempts": history.attempts,
        "last_mindsolve": latest_any.reviewed_at.isoformat() if latest_any else "",
        "last_result": last_result,
        "consecutive_passes": consecutive_passes,
        "interval_days": interval,
        "overdue_days": max(0, (today - due).days),
        "failure_stage": failure_stage,
    }


def generate_rows(repo: Path, log_path: Path, today: date) -> list[dict[str, str | int]]:
    histories = load_histories(repo)
    reviews = parse_reviews(log_path, histories)
    by_problem: dict[str, list[Review]] = defaultdict(list)
    for review in reviews:
        by_problem[review.problem].append(review)
    rows = [build_row(history, by_problem[history.problem], today) for history in histories]
    return sorted(rows, key=lambda row: (row["due_date"], row["problem"]))


def write_rows(path: Path, rows: list[dict[str, str | int]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    descriptor, temporary_name = tempfile.mkstemp(prefix=f".{path.name}.", dir=path.parent)
    try:
        with os.fdopen(descriptor, "w", newline="", encoding="utf-8") as handle:
            writer = csv.DictWriter(handle, fieldnames=OUTPUT_FIELDS)
            writer.writeheader()
            writer.writerows(rows)
        os.replace(temporary_name, path)
    except BaseException:
        try:
            os.unlink(temporary_name)
        except FileNotFoundError:
            pass
        raise


def has_activity(repo: Path, activity_date: date) -> bool:
    start = datetime.combine(activity_date, time.min, TIMEZONE)
    end = start + timedelta(days=1)
    pathspecs = [f":(top,glob)*{suffix}" for suffix in sorted(SOURCE_SUFFIXES)]
    pathspecs.append(":(top)mindsolve-log.csv")
    output = run_git(
        repo,
        "log",
        "--format=%aE%x09%cI",
        f"--since={start.isoformat()}",
        f"--until={end.isoformat()}",
        "--",
        *pathspecs,
    )
    for line in output.splitlines():
        if not line:
            continue
        email, timestamp = line.split("\t", 1)
        committed_at = parse_git_datetime(timestamp)
        if start <= committed_at < end and "github-actions[bot]" not in email:
            return True
    return False


def parse_args(argv: list[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo", type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument("--log", type=Path)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--today", type=date.fromisoformat)
    parser.add_argument("--check-activity", type=date.fromisoformat)
    return parser.parse_args(argv)


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv or sys.argv[1:])
    repo = args.repo.resolve()
    try:
        if args.check_activity:
            return 0 if has_activity(repo, args.check_activity) else 3
        log_path = args.log or repo / "mindsolve-log.csv"
        output_path = args.output or repo / "review-schedule.csv"
        today = args.today or datetime.now(TIMEZONE).date()
        rows = generate_rows(repo, log_path, today)
        write_rows(output_path, rows)
    except ScheduleError as error:
        print(f"error: {error}", file=sys.stderr)
        return 2
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
