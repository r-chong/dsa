class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();

        int bestStart = 0;
        int bestLen = 1;

        for (int center = 0; center < n; center++) {
            // Odd-length palindrome
            int l = center, r = center;

            while (l >= 0 && r < n && s[l] == s[r]) {
                int len = r - l + 1;
                // s[l..r] is a palindrome

                if (len > bestLen) {
                    bestStart = l;
                    bestLen = len;
                }

                l--;
                r++;
            }

            // Even-length palindrome
            l = center;
            r = center + 1;

            while (l >= 0 && r < n && s[l] == s[r]) {
                int len = r - l + 1;
                // s[l..r] is a palindrome

                if (len > bestLen) {
                    bestStart = l;
                    bestLen = len;
                }

                l--;
                r++;
            }
        }

        return s.substr(bestStart, bestLen);
    }
};
// divergences
// - didn't respect the two pointer solution. Thought DP would be the same as "palindromic substrings"
// - just declare len at top of loop
// - did a read of l,r after updating l,r causing OOB

class Solution {
public:
    string longestPalindrome(string s) {
        int bestLen = 1;
        int bestStart = 0;

        for (int center = 0; center < s.size(); center++) {
            // odd center
            int l = center;
            int r = center;

            while (l >= 0 && r < s.size() && (s[l] == s[r])) {
                int len = r - l + 1;

                if (len > bestLen) {
                    bestLen = len;
                    bestStart = l;
                }

                l--;
                r++;
            }

            // even center
            l = center;
            r = center + 1;

            while (l >= 0 && r < s.size() && (s[l] == s[r])) {
                int len = r - l + 1;

                if (len > bestLen) {
                    bestLen = len;
                    bestStart = l;
                }

                l--;
                r++;
            }
        }

        return s.substr(bestStart, bestLen);
    }
};
// divergences:
// - got ahead of myself; need to set bestLen and bestStart to the right items