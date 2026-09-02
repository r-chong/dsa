class Solution {
    int visitHouse(int i, bool robbedFirst, vector<int>&memo, vector<int>&nums) {
        if (nums.size() == 1) return nums[0];
        if (i >= nums.size()) return 0;
        if (memo[i] != -1) return memo[i];
        if (i == nums.size() - 1 && robbedFirst) return 0;

        int skip = 0;
        int rob = 0;
        
        if (i == 0 && !robbedFirst || i > 0) {
            skip = visitHouse(i + 1, robbedFirst, memo, nums);
        }
        if (i == 0 && robbedFirst || i > 0) {
            rob = nums[i] + visitHouse(i + 2, robbedFirst, memo, nums);
        }

        return memo[i] = max(skip, rob);
    }
public:
    // TC: O(n), SC: O(n)
    int rob(vector<int>& nums) {
        int n = nums.size();

        vector<int> memo;
        memo.resize(n, -1);

        int robFirst = visitHouse(0, true, memo, nums);
        memo.assign(n, -1);
        int noRobFirst = visitHouse(0, false, memo, nums);

        return max(robFirst, noRobFirst);
    }
};
// divergences:
// - didn't force cases for the first value meaning "robFirst" didn't represent accurately
// - didn't handle nums.size()==1
// - forgot to clear memo before reusing for second case

// cleaner sol:
class Solution {
    vector<vector<int>> memo;

    int traverse(int i, bool robbedFirst, vector<int>& nums) {
        if (i >= nums.size()) return 0;
        if (memo[i][robbedFirst] != -1) return memo[i][robbedFirst];

        int rob = 0;
        if (i < nums.size() - 1 || i == nums.size() - 1 && !robbedFirst) {
            rob = nums[i] + traverse(i + 2, robbedFirst, nums);
        }
        int skip = traverse(i + 1, robbedFirst, nums);

        return memo[i][robbedFirst] = max(rob, skip);
    }
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        memo = vector<vector<int>>(n, vector<int>(2, -1));

        return max(traverse(1, false, nums), nums[0] + traverse(2, true, nums));
    }
};
// divergences:
// - did not apply robbing logic uniformly in parent rob() - do nums[0] + traverse ...