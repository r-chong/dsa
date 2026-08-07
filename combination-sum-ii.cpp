class Solution {
    void backtrack(int i, int sum, bool prevChosen, vector<int> &current, vector<int> &candidates, int target, vector<vector<int>> &res) {
        if (i == candidates.size()) {
            if (sum == target) {
                res.push_back(current);
            }
            return;
        }
        if (sum > target) {
            return;
        }

        // exclude
        backtrack(i + 1, sum, false, current, candidates, target, res);

        // conditionally include 1 copy, satifying uniqueness
        bool forbidden = !prevChosen && i > 0 && candidates[i] == candidates[i - 1];
        if (!forbidden) {
            current.push_back(candidates[i]);
            backtrack(i + 1, sum + candidates[i], true, current, candidates, target, res);
            current.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> current;
        vector<vector<int>> res;

        sort(candidates.begin(), candidates.end());

        backtrack(0, 0, false, current, candidates, target, res);

        return res;
    }
};
// divergences:
// - wrote `candidates` as `nums`
// - order of forbidden && items matters. if candidates[i] == candidates[i - 1] evaluated before i < 0 then it crashes.