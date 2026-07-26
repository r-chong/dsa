class Solution {
    void backtrack(int i, int sum, vector<int> &current, vector<int> &candidates, int target, vector<vector<int>> &res) {
        if (i == candidates.size()) {
            if (sum == target) {
                res.push_back(current);
            }
            return;
        }
        if (sum > target) {
            return;
        }
        // exclude (move onto next number)
        backtrack(i + 1, sum, current, candidates, target, res);

        // include 1+ copies
        current.push_back(candidates[i]);
        backtrack(i, sum + candidates[i], current, candidates, target, res);
        current.pop_back();
    }
public:
    // Time: O(2^(n + target / m))
    // Space: O(n + target / m) excluding output
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> current;
        vector<vector<int>> res;

        backtrack(0, 0, current, candidates, target, res);

        return res;
    }
};
// divergences:
// - inserted arguments into pop_back
// - copied format of the subsets problem, but this one you may reuse the number.
// - couldn't figure out sum > target case