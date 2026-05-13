class Solution {
public:
    int rob(vector<int>& nums) {
        // dp

        int n = nums.size();

        // early end conditions
        // base cases
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return nums[0];
        }

        vector<int> dp(n);

        // start at left side (we go left to right in time)
        dp[0] = nums[0];
        dp[1] = std::max(dp[0], nums[1]);

        for (int i = 2; i < n; i++) {
            int skip = dp[i - 1];
            int take = nums[i] + dp[i - 2];

            dp[i] = std::max(skip, take);
        }

        // just want one value
        return dp[n - 1];
    }
};