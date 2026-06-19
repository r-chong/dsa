class Solution {
public:
    // could be a deque
    int lengthOfLongestSubstring(string s) {
        int n = s.size();

        // base cases to prevent index errors
        if (n == 0) return 0;
        if (n == 1) return 1;

        int l = 0;
        int r = 0;

        int longest = 0;

        // map the char to the last index it was seen
        unordered_map<char, int>visited;
        while (r < n) {
            char c = s[r];

            if (visited.find(c) != visited.end() && visited[c] >= l) {
                l = visited[c] + 1;
            }

            visited[c] = r;
            longest = max(longest, r - l + 1);
            r++;
        }
        return longest;
    }
};
// divergences:
// - missed the visited[c] >= l condition, so when a `c` was "reset" it was still != visited.end()
// - my streak value was counting the number of values between the last time we saw this char, and now. 
// the correct calculation is r - l + 1