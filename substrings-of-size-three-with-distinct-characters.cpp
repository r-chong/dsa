class Solution {
public:
    // TC: O(n), SC: O(1)
    int countGoodSubstringsWithJustR(string s) {
        int len = 3;
        int count = 0;

        vector<int> freq(128);
        int duplicates = 0;

        for (int i = 0; i < s.size(); i++) {
            // it will never go beyond two
            if (++freq[s[i]] == 2)
                duplicates++;

            if (i >= len) {
                if (--freq[s[i - len]] == 1) {
                    duplicates--;
                }
            }

            // at least one window, (without this case we count the building of window)
            if (i >= len - 1 && duplicates == 0) {
                count++;
            }
        }

        return count;
    }
    // divergences:
    // - didn't know how to only update left/right
    // - the duplicate counter seems to be similar to past problems, like "needs" in minimum substring however i treated as one-offs

    // TC: O(n), SC: O(1)
    int countGoodSubstrings(string s) {
        int len = 3;
        int count = 0;

        vector<int> freq(128);
        int duplicates = 0;

        int l = 0;

        for (int r = 0; r < s.size(); r++) {
            // add right character and update window state
            if (++freq[s[r]] == 2)
                duplicates++;

            // you can choose to hide the l variable of sliding window
            // with i representing r, since len is fixed at 3 you can derive l by doing r - len.
            // but this part makes more sense to me explicitly mentioning that we maintain validity of the window in terms of left and right side.
            
            // remove left character and update window state
            if (r - l + 1 > len) {
                if (--freq[s[l]] == 1) {
                    duplicates--;
                }

                l++;
            }

            if (r - l + 1 == len && duplicates == 0) {
                count++;
            }
        }

        return count;
    }
};