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

// simpler I believe
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.size() > s2.size()) return false;
        vector<int> has(26, 0);
        vector<int> need(26, 0);

        for (int i = 0; i < s1.size(); i++) {
            need[s1[i] - 'a']++;
        }

        // init left and right side of window
        int l = 0;
        int r = 0;

        while (r < s2.size()) {
            has[s2[r] - 'a']++;
            r++;

            // grow window to size of s1   
            if (r < s1.size()) {
                continue;
            }

            if (has == need) return true;
            
            has[s2[l] - 'a']--;
            l++;
        }

        return false;
    }
};
// divergences:
// - forgot to populate need
// - didnt index by letter
// - when using a loop to go through i < 128, was indexing by letter which OOB
// - knew general idea but didnt have good thinking
// - could've just directly compared vectors
// - knew i should shrink window but didnt know where to put it
// - set r to 1 at start
// - didnt consider edge case of s1 > s2