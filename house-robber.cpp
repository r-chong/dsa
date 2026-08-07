class Solution {
public:
    // TC: O(n), SC: O(n)
    int robIterative(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        vector<int> memo(n);

        // start at left side (we go left to right in time)
        memo[0] = nums[0];
        memo[1] = max(memo[0], nums[1]);

        for (int i = 2; i < n; i++) {
            int skip = memo[i - 1];
            int take = nums[i] + memo[i - 2];

            memo[i] = max(skip, take);
        }

        return memo[n - 1];
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
    int visitHouse(int i, vector<int> &memo, vector<int>&nums) {
        if (i >= nums.size()) return 0;
        if (memo[i] != -1) return memo[i];

        int skip = visitHouse(i + 1, memo, nums);
        int rob = nums[i] + visitHouse(i + 2, memo, nums);

        return memo[i] = max(skip, rob);
    }
    int robRecursive(vector<int>& nums) {
        vector<int> memo;
        memo.resize(nums.size(), -1);

        return visitHouse(0, memo, nums);
    }
    // divergences:
    // - didn't add DP part
    // - changed return of robRecursive
    // - unnecessary robbedPrev variable
    // - didn't understand that the naive version takes up MEMORY although not space
};
    