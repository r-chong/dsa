// TC: O(nlogn), SC: O(1)
// This was a brute force as the constraints are: You must write an algorithm that runs in O(n) time.
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;
        int n = nums.size();

        sort(nums.begin(), nums.end());

        int max_streak = 1;
        int streak = 1;
        int prev = nums[0]; 
        for (int i = 1; i < n; i++) {
            if (nums[i] == prev) {
                continue;
            } else if ((nums[i] - prev) == 1) {
                streak++;
            } else {
                streak = 1;
            }

            max_streak = max(streak, max_streak);
            prev = nums[i];
        }

        return max_streak;
    }
};
// divergences:
// - updated max streak only when the streak ended which ignores the case where the streak lasts until the end
// - thought I have for loop go until n - 1 instead of n.
// - ignored case for equal elements
// - ignored case for empty nums array