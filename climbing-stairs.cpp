// Note: this file is purely for reference and will not compile.

class Solution {
public:
    // DFS brute force, work stair 0 upward
    // TC: O(2^n), SC: O(n) 
    // Each branch has two calls, and the longest path is from 0 to n, meaning 2^n calls
    // Correctness: 
    int dfs(int i, int n) {
        if (i > n) {
            return 0;
        } if (i == n) {
            return 1;
        }

        return dfs(i + 1, n) + dfs(i + 2, n);
    }

    int climbStairs(int n) {
        return dfs(0, n);
    }

    // DFS memoized, work from stair 0 upward
    // Note that this is not "bottom up DP." bottom-up DP uses a fixed loop order whereas this just memoizes on demand. 
    // TC: O(n), SC: O(n) 
    int dfs(int i, int n, std::vector<int> &memo) {
        if (i > n) {
            return 0;
        } if (i == n) {
            return 1;
        }

        if (memo[i] != -1) {
            return memo[i];
        }

        memo[i] = dfs(i + 1, n, memo) + dfs(i + 2, n, memo);
        return memo[i];
    }

    int climbStairs(int n) {
        std::vector<int> memo(n + 1, -1);

        return dfs(0, n, memo);
    }

    // DP SECTION:
    // Two equivalent ways to define the DP state:
    //
    // 1. i = current stair:
    //    ways(i) = ways(i + 1) + ways(i + 2)
    //
    // 2. n = stairs remaining:
    //    ways(n) = ways(n - 1) + ways(n - 2)
    //

    // i = current stair
    // TC: O(n), SC: O(n)
    // each subproblem (index) is computed once. 
    // Why DP:
    // - overlapping subproblems; different decisions (steps) can reach the same i
    // - each i collapses history - The current state i contains all the information needed to determine the future. How you reached i does not matter.
    int ways(int i, vector<int> &memo, int n) {
        if (i > n) return 0;
        if (i == n) return 1;
        if (memo[i] != -1) return memo[i];

        memo[i] = ways(i + 1, memo, n) + ways(i + 2, memo, n);
        return memo[i];
    }
    int climbStairs(int n) {   
        vector<int> memo;
        memo.resize(n, -1);

        return ways(0, memo, n);
    }
    // divergences:
    // - messed up order of the base cases

    // Top down recursive memoization, state = # stairs remaining
    // TC: O(n), SC: O(n)
    int dfs(int n, std::vector<int> &memo) {
        if (n < 0) {
            return 0;
        } if (n == 0) {
            return 1;
        } if (memo[n] != -1) {
            return memo[n];
        }

        memo[n] = dfs(n - 1, memo) + dfs(n - 2, memo);
        return memo[n];
    }
    int climbStairs(int n) {
        std::vector<int> memo(n + 1, -1);

        return dfs(n, memo);
    }

    // Iterative bottom up DP
    // TC: O(n), SC: O(n)
    int climbStairs(int n) {
        std::vector<int> dp(n + 2, 0);
        dp[0] = 1;

        for (int i = 0; i < n; i++) {
            dp[i + 1] += dp[i];
            dp[i + 2] += dp[i];
        } 

        // simply discard the last 2 items
        return dp[n];       
    }

    // Iterative bottom up DP with space optimization
    // TC: O(n), SC: O(1)
    int climbStairs(int n) {        
        int prev2 = 1;
        int prev1 = 1;

        for (int i = 2; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        } 

        return prev1;       
    }
};