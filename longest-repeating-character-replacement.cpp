class Solution {
public:
    int characterReplacementBruteForce(string s, int k) {
        int n = s.size();
        int best = 0;

        for (int l = 0; l < n; l++) {
            unordered_map<char, int> freq;
            int maxFreq = 0;

            for (int r = l; r < n; r++) {
                char c = s[r];

                freq[c]++;
                maxFreq = max(maxFreq, freq[c]);

                int length = r - l + 1;

                int replacementsNeeded = length - maxFreq;

                if (replacementsNeeded <= k) {
                    best = max(best, length);
                }
            }
            
            return best;
        }
    };
    // divergences:
    // - initially thought this was a trie due to string combinations... we actually calculate replacements needed by math
    // - condition should be r = l not l + 1 

   int characterReplacementSlidingWindow(string s, int k) {
        int n = s.size();
        int best = 0;
	
        int l = 0;
        int r = 0;

        unordered_map<char, int> freq;
        int maxFreq = 0;

        while (r < n) {
            char c = s[r];

            freq[c]++;
            maxFreq = max(maxFreq, freq[c]);

            int length = r - l + 1;	
            int replacementsNeeded = length - maxFreq;

            if (replacementsNeeded <= k) {
                best = max(best, length);
            } else {
                freq[s[l]]--;
                l++;
            }
            r++;
	    } 
        
        return best;
    }
};
// divergences:
// - forgot freq[s[l]]--
// - used l < r as condition instead of r < n... r is the main variable, l just trails behind
// - freq and maxFreq should be persistent instead of being reinitialized each time.. so out of the loop