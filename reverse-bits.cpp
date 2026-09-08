// 2026-02-02
class Solution {
public:
    int reverseBits(int n) {
        unsigned int res = 0;

        for (int i = 0; i < 32; ++i) {
            res <<= 1;
            res |= (n & 1);
            n >>= 1;
        }

        return res;
    }
};

// s <<= 1 is shift left by 1
// a |= b is the same as a = a | b

// 2026-09-08 (i understand it more)
class Solution {
public:
    // TC: O(1) (always 32 iteration), SC: O(1)
    int reverseBits(int n) {
        uint32_t ans = 0;

        // for all 32 places in uint32
        for (int i = 0; i < 32; i++) {
            // extract from right of n
            uint32_t bit = n & 1;

            n >>= 1;
            ans <<= 1;

            ans |= bit;
        }

        return ans;
    }
};
// divergences:
// - thought i could just go through n but since we're reversing, the leading 0's of n become trailing 0's of new