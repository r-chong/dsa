// Note: this file is purely for reference and will not compile.

class Solution {
public:
    // DFS brute force, work stair 0 upward
    // TC: O(2^n), SC: O(1) 
    // Each branch has two calls, and the longest path is from 0 to n, meaning 2^n calls
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

    // Top down recursive memoization, n = stairs remaining aka work downwards (version 1)
    // TC: O(n), SC: O(n)
    int climbStairs1(int n) {
        std::unordered_map<int, int> visited;

        if (n < 0) return 0;
        if (n == 0) return 1;
        
        if (visited.contains(n)) {   
            return visited[n];
        } 

        visited[n] = climbStairs(n - 1) + climbStairs(n - 2);
        return visited[n];
    }

    // Top down recursive memoization, n = stairs remaining aka work downwards (version 2)
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