class Solution {
    // for all possible amounts
    vector<vector<int>> memo;

    // TC: O(amount * n^2), SC: O(n * amount)
    // STATES * WORK
    // n = number of coins
    int combinations(int amount, vector<int>& coins, int i) {
        if (amount < 0) return 0;
        if (amount == 0) return 1;
        if (memo[amount][i] != -1) return memo[amount][i];

        int count = 0;
        for (int j = i; j < coins.size(); j++) {
            count += combinations(amount - coins[j], coins, j);
        }

        return memo[amount][i] = count;
    }
public:
    int change(int amount, vector<int>& coins) {        
        memo = vector<vector<int>>(
            amount + 1,
            vector<int>(coins.size(), -1)
        );

        return combinations(amount, coins, 0);
    }
};
// divergences:
// - didn't realize I was computing permutation instead of combination; therefore overcounted
// - didn't see the 2nd dimension: i, as a solution to removing double counting
// - set up double vector memo wrong
// - hardcoded a base case which was wrong - amount == 0 returns 1 because successfully making exactly 0
//   represents one completed combination