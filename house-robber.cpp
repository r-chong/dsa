class Solution {
public:
    // TC: O(n), SC: O(n)
    int robIterative(vector<int>& nums) {
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
    
    // RECURSIVE SOLUTION

    // TC: O(2^n), SC: O(n)
    // although we don't use additional STORAGE, each recursive call stays on the call stack until its children return, using memory.
    // n = size of nums
    int visitHouseNaive(int i, vector<int>&nums) {
        if (i >= nums.size()) return 0;

        int skip = visitHouse(i + 1, nums);
        int rob = nums[i] + visitHouse(i + 2, nums);

        return max(skip, rob);
    }

    // TC: O(n), SC: O(n) auxilary
    // n = size of nums
    // O(n) as each i is solved once using DP
    int visitHouse(int i, vector<int> &dp, vector<int>&nums) {
        if (i >= nums.size()) return 0;
        if (dp[i] != -1) return dp[i];

        int skip = visitHouse(i + 1, dp, nums);

        int rob = nums[i] + visitHouse(i + 2, dp, nums);

        dp[i] = max(skip, rob);
        return dp[i];
    }
    
    int robRecursive(vector<int>& nums) {
        vector<int> dp;
        dp.resize(nums.size(), -1);

        return visitHouse(0, dp, nums);
    }
    // divergences:
    // - didn't add DP part
    // - changed return of robRecursive
    // - unnecessary robbedPrev variable
    // - didn't understand that the naive version takes up MEMORY although not space
    // - 
};
    