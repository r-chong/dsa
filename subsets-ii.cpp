class Solution {
    void backtrack(int i, vector<int> &current, vector<int> &nums, set<vector<int>> &uniqueSubsets) {
        if (i == nums.size()) {
            uniqueSubsets.insert(current);
            return;
        }

        backtrack(i + 1, current, nums, uniqueSubsets);
        current.push_back(nums[i]);
        backtrack(i + 1, current, nums, uniqueSubsets);
        current.pop_back();
    }
public:
    // "brute force" duplicate and clean-up solution
    // TC: O(n^2 * 2^n)
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> current;
        set<vector<int>> uniqueSubsets;
        sort(nums.begin(), nums.end());

        backtrack(0, current, nums, uniqueSubsets);

        vector<vector<int>> res(uniqueSubsets.begin(), uniqueSubsets.end());

        return res;
    }
};
// divergences:
// - set up constructor with set wrong. didn't use uniqueSubsets.begin() and end()
// - didn't find and replace all res so i had to run multiple times
// - didn't sort(), I still don't fully get why we need this