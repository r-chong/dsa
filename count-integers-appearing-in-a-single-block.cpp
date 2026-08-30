class Solution {
public:
    int countSpecialIntegers(vector<int>& nums) {
        int curr = 0;
        unordered_map<int, int> seen;
        int count = 0;
        
        for (int i = 0; i < nums.size(); i++){
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            } else {
                seen[nums[i]]++;
            }
        }

        for (auto [x, occurrences] : seen) {
            if (occurrences == 1) count++;
        }

        return count;
    }
};©leetcode