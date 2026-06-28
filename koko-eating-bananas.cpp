class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int max_idx = max_element(piles.begin(), piles.end()) - piles.begin();

        int lo = 1;
        int hi = piles[max_idx];

        while (lo <= hi) {
            int k = lo + (hi - lo) / 2;

            long long hours = 0;
            for (int i = 0; i < piles.size(); i++) {
                hours += (1LL * piles[i] + k - 1) / k;
            }

            if (hours <= h) {
                // too slow
                hi = k - 1;
            } else {
                // too fast
                lo = k + 1;
            }
        }
        return lo;
    }
};
// divergences:
// - wasnt sure while loop condition
// - didnt have the binary search space (it clicked after seeing first TLE)
// - binary search index changing directions
// - need both hi and lo, not just lo