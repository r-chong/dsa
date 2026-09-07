class Solution {
    const int INF = 1e9;
    unordered_map<int, int> memo;

    // TC: O(A * C), SC: O(A)
    // we have # amounts (A) states, and most work per state is C
    // the invocations of DFS can be up to A on the call stack
    int dfs(vector<int>& coins, int amount) {
        // f(amount) = min(f(amount - c_i)) for all c_i in coins
        if (amount == 0) return 0;
        if (amount < 0) return INF;
        if (memo.contains(amount)) return memo[amount];

        int minCoins = INF;
        for (int c : coins) {
            minCoins = min(minCoins, 1 + dfs(coins, amount - c));
        }

        return memo[amount] = minCoins;
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        memo = unordered_map<int, int>();

        int ans = dfs(coins, amount);

        if (ans == INF) return -1;

        return ans;
    }
};
// divergences:
// - got confused - the recurrence I defined wasn't the one I was coding... and I wasn't. thinking correctly about base case
// - needed identical non main function just for the invalid case (-1 was messing up recurrence)
// - didnt replace all with non main function