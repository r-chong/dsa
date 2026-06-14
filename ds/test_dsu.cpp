#include <iostream>
#include <string>
#include "disjoint-set-union.cpp"

class TestDSU {
private:
    int tests_run = 0;
    int tests_passed = 0;

    void check(bool condition, const std::string& name) {
        tests_run++;
        if (condition) {
            tests_passed++;
            std::cout << "PASS: " << name << std::endl;
        } else {
            std::cout << "FAIL: " << name << std::endl;
        }
    }

public:
    void run_all_tests() {
        std::cout << "\n=== DSU behavior tests ===" << std::endl;

        test_basics_and_initial_count();
        test_unite_with_non_root_inputs();
        test_duplicate_union_and_count_stability();
        test_mixed_connected_and_not_connected_with_count();
        test_chain_of_component_merges();
        test_union_order_independence();

        print_summary();
    }

private:
    void test_basics_and_initial_count() {
        std::cout << "\n--- basics and initial count ---" << std::endl;
        DSU dsu(3);

        check(dsu.connected(0, 0), "self connectivity for 0");
        check(!dsu.connected(0, 1), "different nodes start disconnected");
        check(dsu.count() == 3, "initial count equals n");
    }

    void test_unite_with_non_root_inputs() {
        std::cout << "\n--- unite with non-root inputs ---" << std::endl;
        DSU dsu(4);

        check(dsu.unite(0, 1), "unite(0,1) succeeds");
        check(dsu.unite(2, 3), "unite(2,3) succeeds");
        check(dsu.unite(1, 3), "unite(non-root, non-root) succeeds");

        check(dsu.connected(0, 3), "components merged through non-root inputs");
        check(dsu.connected(1, 2), "all four nodes now connected");
        check(dsu.count() == 1, "count reaches 1 after full merge");
    }

    void test_duplicate_union_and_count_stability() {
        std::cout << "\n--- duplicate union and count stability ---" << std::endl;
        DSU dsu(3);

        check(dsu.unite(0, 1), "first unite returns true");
        check(dsu.count() == 2, "count decremented once after first unite");

        check(!dsu.unite(0, 1), "duplicate unite returns false");
        check(!dsu.unite(1, 0), "reverse duplicate unite returns false");
        check(dsu.count() == 2, "count unchanged after duplicate unites");
    }

    void test_mixed_connected_and_not_connected_with_count() {
        std::cout << "\n--- mixed connected/not-connected and count ---" << std::endl;
        DSU dsu(6);

        check(dsu.unite(0, 1), "unite(0,1)");
        check(dsu.unite(2, 3), "unite(2,3)");

        check(dsu.connected(0, 1), "0 and 1 connected");
        check(dsu.connected(2, 3), "2 and 3 connected");
        check(!dsu.connected(0, 2), "0 and 2 not connected");
        check(!dsu.connected(1, 5), "1 and 5 not connected");
        check(dsu.count() == 4, "count is 4 after two successful unites");
    }

    void test_chain_of_component_merges() {
        std::cout << "\n--- chain of component merges ---" << std::endl;
        DSU dsu(6);

        check(dsu.unite(0, 1), "unite(0,1)");
        check(dsu.unite(2, 3), "unite(2,3)");
        check(dsu.unite(4, 5), "unite(4,5)");
        check(dsu.unite(1, 3), "merge first two components via non-roots");
        check(dsu.unite(3, 5), "merge resulting component with third via non-roots");

        check(dsu.connected(0, 5), "0 and 5 connected after chain merges");
        check(dsu.connected(1, 4), "1 and 4 connected after chain merges");
        check(dsu.count() == 1, "count is 1 when all nodes connected");
    }

    void test_union_order_independence() {
        std::cout << "\n--- union order independence ---" << std::endl;
        DSU a(5);
        DSU b(5);

        check(a.unite(0, 1), "a unite(0,1)");
        check(a.unite(2, 4), "a unite(2,4)");
        check(a.unite(1, 4), "a final merge");

        check(b.unite(4, 2), "b unite(4,2)");
        check(b.unite(1, 0), "b unite(1,0)");
        check(b.unite(4, 0), "b final merge");

        check(a.connected(0, 2), "a has expected connectivity");
        check(b.connected(0, 2), "b has expected connectivity");
        check(a.count() == b.count(), "same count regardless of union order");
    }

    void print_summary() {
        std::cout << "\n=== Summary ===" << std::endl;
        std::cout << "Tests run: " << tests_run << std::endl;
        std::cout << "Passed: " << tests_passed << std::endl;
        std::cout << "Failed: " << (tests_run - tests_passed) << std::endl;
    }
};

int main() {
    TestDSU suite;
    suite.run_all_tests();
    return 0;
}
