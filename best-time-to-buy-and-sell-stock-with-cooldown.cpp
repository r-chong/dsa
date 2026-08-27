class Solution {
    vector<int> p;

    int profitAt(int i, bool holding) {
        if (i >= p.size()) return 0;

        if (holding) {
            // sell today, or not sell today
            return max(p[i] + profitAt(i + 2, false), profitAt(i + 1, true));
        } else {
            // buy today, or not buy today
            return max(-p[i] + profitAt(i + 1, true), profitAt(i + 1, false));
        }
    }
public:
    // TC: O(2^n), SC: O(n) (call stack)
    // There are 2n possible (i, holding) states.
    // Each state branches into up to 2 recursive calls.
    // The same states may be recomputed many times.
    int maxProfit(vector<int>& prices) {
        p = prices;

        return profitAt(0, false);
    }
};
// divergences:
// - didn't consider using prices directly in calculation
// - put global reference instead of just global vector<int>

// top down recursive sol
class Solution {
    vector<int> p;
    vector<vector<int>> memo;

    int profitAt(int i, bool holding) {
        if (i >= p.size()) return 0;
        if (memo[i][holding] != -1) return memo[i][holding];

        int ans = 0;

        // store memo[i][not holding, holding]
        if (holding) {
            // sell today, or not sell today
            ans = max(p[i] + profitAt(i + 2, false), profitAt(i + 1, true));
        } else {
            // buy today, or not buy today
            ans = max(-p[i] + profitAt(i + 1, true), profitAt(i + 1, false));
        }

        return memo[i][holding] = ans;
    }
public:
    // TC: O(n), SC: O(n)
    // There are 2n possible (i, holding) states.
    // Each state does O(1) work.
    // Each state is computed at most once.
    int maxProfit(vector<int>& prices) {
        p = prices;
        memo = vector<vector<int>>(p.size(), vector<int>(2, -1));

        return profitAt(0, false);
    }
};
// divergences:
// - forgot to do memo[i] i directly accessed the 2nd dimension

// convergences:
// - used boolean as indexer