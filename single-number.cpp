// go through all nums and mark as visited
// if visited then mark as 0... so basically, flip
// the last 1 standing is that one

// TC: O(n), SC: O(1)
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int mask = 0;
        int ans = 0;

        for (int i = 0; i < nums.size(); i++) {
            mask = mask ^ nums[i];
        }

        return mask;
    }
};
// divergences:
// - initially didn't know about flip
// ^= for flip, |= for checking bit, & for compare, (1 << i) for check that index, (i << nums[i]) for check that number
// - for logging, use cout << bitset<8>(x) << endl
// - thought I needed a separate ans as below:
// - but the final mask is literally the single number.

        // for (int i = 0; i < nums.size(); i++) {
        //     if (mask & (1 << i)) {
        //         ans = nums[i];
        //     }
        // }

// - initially had solution below which passes on neetcode (he does not check for negative tests)

class Solution {
public:
    int singleNumberNoNegativeCheck(vector<int>& nums) {
        int mask = 0;
        int ans = 0;

        // go through all nums and mark as visited
        // if visited then mark as 0
        // so basically, flip
        // then the last 1 is that one
        for (int i = 0; i < nums.size(); i++) {
            mask ^= (1 << nums[i]);
        }

        for (int i = 0; i < nums.size(); i++) {
            if (mask & (1 << nums[i])) {
                ans = nums[i];
            }
        }

        return ans;
    }
};

