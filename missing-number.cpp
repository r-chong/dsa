// Bitwise XOR

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        // order does not matter
        int n = nums.size();
        int ans = 0;

        // must generate nums as an integer
        for (int i = 0; i < n; i++) {
            ans ^= nums[i];
        }

        // then go from 0..n
        // ensure not to be off by one (n-1)
        for (int i = 0; i <= n; i++) {
            ans ^= i;
        }

        return ans;
    }
};

// Alternatively
// class Solution {
// public:
//     int missingNumber(vector<int>& nums) {
//         // order does not matter
//         int n = nums.size();
//         int ans = n;

//         for (int i = 0; i <= n; i++) {
//             ans ^= nums[i];
//             ans ^= i;
//         }

//         return ans;
//     }
// };

// Original: suboptimal
// O(nlogn)

/*
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        // loop through [0, n)
        // if != i then return that number

        std::sort(nums.begin(), nums.end());

        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if (nums[i] != i) {
                return i;
            }
        }

        // if not from [0, n), then it is n
        return n;
    }
};
*/