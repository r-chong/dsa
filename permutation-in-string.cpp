// brute force
class Solution {
public:
    // s2 >= s1 is invalid if one char in s1 is not in s2
    bool checkInclusion(string s1, string s2) {
        int n = s2.size();
        // fixed sliding window of size s1.size()
        int w = s1.size();
        if (w > n) return false;

        array<int, 26> freq1 {};
        array<int, 26> freq2 {};

        for (char c : s1) {
            freq1[c - 'a']++;
        }

        for (int i = 0; i < w; i++) {
            freq2[s2[i] - 'a']++;
        }

        if (freq1 == freq2) return true;

        for (int r = w; r < s2.size(); r++) {
            freq2[s2[r - w] - 'a']--;
            freq2[s2[r] - 'a']++;

            if (freq1 == freq2) return true;
        }

        return false;
    }
    // divergences:
    // - thought that it could just include the frequency, but the permutation has to be whole
    // - must initialize arrays even with empty {}
    // - forgot - 'a' sometime

    bool checkInclusion(string s1, string s2) {
        vector<int> needs(128, 0);
        int missing = s1.size();

        for (char c : s1) {
            needs[c]++;
        }
        
        vector<int> has(128, 0);
        int l = 0;

        for (int r = 0; r < s2.size(); r++) {
            char right = s2[r];
            has[right]++;

            // this newly-added copy was actually needed
            if (has[right] <= needs[right]) {
                missing--;
            }

            while (r - l + 1 > s1.size()) {
                char left = s2[l];

                // Are we removing an occurrence that was actually needed?
                if (has[left] <= needs[left]) {
                    missing++;
                }

                has[left]--;
                l++;
            }

            if (missing == 0) {
                return true;
            }
        }

        return false;
    }
    // divergences:
    // - line 54:has[right] <= needs[right] - the converse (has[left] <= needs[left]) is wrong when checking RHS, that counts all non-needed chars
    // - didn't know what to do with LHS
};