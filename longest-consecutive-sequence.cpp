// TC: O(nlogn), SC: O(1)
// This was a brute force. The real constraints are: You must write an algorithm that runs in O(n) time.
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

// O(n) !! The main idea here is we can utilize the O(1) nature of sets, start SOMEWHERE in the set and access the sequence 1 by 1 until exhausting that given streak

// Solution with set - version 1
// - pick any point and find the entire contiguous streak and then if other parts are STILL in seen then those are separate contiguous streaks 
// - if there is none to left and right, it means we have streak of one.
// - I find this one intuitive.
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return 1;

        unordered_set<int> seen(nums.begin(), nums.end());

        int maxStreak = 0;

        while (!seen.empty()) {
            // why a iterator?
            int x = *seen.begin();
            seen.erase(x);

            int streak = 1;

            // walk left
            int left = x - 1;
            while (seen.contains(left)) {
                seen.erase(left);
                left--;
                streak++;
            }

            // walk right
            int right = x + 1;
            while (seen.contains(right)) {
                seen.erase(right);
                right++;
                streak++;
            }

                maxStreak = max(maxStreak, streak);
        }

        return maxStreak;
    }
};

// Solution with set - version 2
// - find any starting point (there is no value immediately prior to it) and traverse forward in the set until there is no value after it
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return 1;

        unordered_set<int> seen(nums.begin(), nums.end());

        int maxStreak = 0;

        for (int x : seen) {
            if (!seen.contains(x - 1)) {
                int streak = 1;
                int curr = x;

                while (seen.contains(curr + 1)) {
                    curr++;
                    streak++;
                }

                maxStreak = max(maxStreak, streak);
            }
        }

        return maxStreak;
    }
};