class Solution {
public:
    int hammingWeight(int n) {
        unsigned int x = n;

        int count = 0;

        while (x != 0) {
            if (x & 1) count++;

            x >>= 1;
        }

        return count;
    }
};
// divergences:
// - shifting returns a value so need to do equal as well
// - Right shift is used here because you’re processing bits from right to left, starting with the least significant bit checked by x & 1.
// - Left shift would move bits away from the bit you’re currently checking.