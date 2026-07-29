class Solution {
    void backtrack(int choicesRemaining, vector<int> &current, set<int> &used, vector<int>& nums, vector<vector<int>> &res) {
        if (choicesRemaining == 0) {
            res.push_back(current);
            return;
        }

        // backtrack on all future possibilities
        for (int i = 0; i < nums.size(); i++) {
            if (used.contains(nums[i])) continue;

            int idx = choicesRemaining - 1;

            current[idx] = nums[i];
            used.insert(nums[i]);
            backtrack(idx, current, used, nums, res);
            used.erase(nums[i]);
            current[idx] = -11;
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<vector<int>> res;
        vector<int> current;
        current.resize(n, -11);
        set<int> used;

        backtrack(n, current, used, nums, res);

        return res;
    }
};
// divergences:
// - missing sort of nums
// - dont need to keep track of where we've filled because we fill left-to-right - it's just choicesRemaining
