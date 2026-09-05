class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        // turn nums into set so its now distinct
        unordered_map<int, int> lastSeen;

        for (int i = 0; i < nums.size(); i++) {
            if (lastSeen.count(nums[i]) && i - lastSeen[nums[i]] <= k) return true;

            lastSeen[nums[i]] = i;
        }

        return false;
    }
};
// divergences:
// - thought we were taking abs of the values not the indices
// - did a sol where I erased key features of the problem: the original index order and the duplicativeness 