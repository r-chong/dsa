class Solution {
    vector<vector<int>> memo;

    int dp(int r, int c, vector<vector<int>>& matrix) {
        if (c < 0 || c >= matrix.size()) return INT_MAX / 2;
        if (r >= matrix.size()) return 0;
        if (memo[r][c] != INT_MAX / 2) return memo[r][c];

        return memo[r][c] = matrix[r][c] + min({
            dp(r + 1, c - 1, matrix),
            dp(r + 1, c, matrix),
            dp(r + 1, c + 1, matrix)
        });
    }
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int ans = INT_MAX;

        memo = vector<vector<int>>(matrix.size(), vector<int>(matrix.size(), INT_MAX / 2));

        for (int c = 0; c < matrix.size(); c++) {
            ans = min(ans, dp(0, c, matrix));
        }

        return ans;
    }
};
// divergences:
// - mainly for default values, i need to make sure that the values I set aren't valid answers.
// - didnt consider infinity as base case for OOB
// - memo[r][c] should not be -1