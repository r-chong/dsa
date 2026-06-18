// TC: O(n), SC: O(1)
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        // Note the sorting; We can start from either side and add a new number depending on how close we are to target

        int left = 0;
        int right = numbers.size() - 1;

        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                return {left + 1, right + 1};
            } else if (sum > target) {
                right--;
            } else {
                left++;
            }
        };

        return {}; // result unreachable by problem constraints
    }
};
// divergences:
// - initially disregarded the sorting constraint
// - hesitated returning {left + 1, right + 1};
