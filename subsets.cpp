class Solution {
    void backtrack(int i, vector<int> &current, vector<int> &nums, vector<vector<int>> &res) {
        if (i == nums.size()) {
            res.push_back(current);
            return;
        }

        backtrack(i + 1, current, nums, res);
        current.push_back(nums[i]);
        backtrack(i + 1, current, nums, res);
        current.pop_back();
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> current;
        vector<vector<int>> res;

        // start off with first element i=0
        // i does NOT represent size.
        backtrack(0, current, nums, res);

        return res;
    }
};
// divergences:
// - minor stuff - forgot to return res and also forgot to leave pop_back() brackets empty
// - tutoring session: https://chatgpt.com/c/6a63c82a-4df4-83ed-9397-043c7cb87bf4