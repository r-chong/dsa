// TC: O(n), SC: O(n)
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int>s;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            s.insert(nums[i]);

            if (s.size() != i + 1) {
                return true;
            }
        }

        return false;
    }
};