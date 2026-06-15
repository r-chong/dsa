class Solution {
public:
    int dfs(int i, int n, vector<int>& cost, vector<int> &memo) {
        if (i > n) return 0;
        if (i == n) return cost[i];
        if(memo[i] != -1) return memo[i];

        memo[i] = min(cost[i] + dfs(i + 1, n, cost, memo), cost[i] + dfs(i + 2, n, cost, memo));
        return memo[i];
    }

    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size() - 1;
        vector<int> memo(n + 2, -1);

        return min(dfs(0, n, cost, memo), dfs(1, n, cost, memo));
    }
};
