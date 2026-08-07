class Solution {
    bool traverse(int i, vector<int>& memo, vector<int>& nums) {
        int n = nums.size();
        if (i >= n - 1) {
            return true;
        }
        if (memo[i] != -1) return memo[i];

        // if we do not return true in here, assume false
        for (int k = 1; k <= nums[i]; k++) {
            if (traverse(i + k, memo, nums)) {
                return memo[i] = 1;
            }
        }

        return memo[i] = 0;
    }
public:
    // TC: O(n^2), SC: O(n)
    // n = size of nums
    // Each index of nums is calculated once, computing one index may loop through up to nums[i] possible jumps
    bool canJump(vector<int>& nums) {
        // -1 means not checked, 0 means no, 1 means yes
        vector<int> memo;
        memo.resize(nums.size(), -1);

        return traverse(0, memo, nums) == 1;
    }
};
// divergences:
// - indexing issue, put if(nums[i] == 0) before index bounds check
// - made traverse return void, meaning we couldn't short circuit on correct answer
// - did not include k == nums[i] in jump calculation