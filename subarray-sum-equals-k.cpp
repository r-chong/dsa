class Solution {
public:
    // TC: O(n^2), SC: O(1)
    int subarraySumBruteForce(vector<int>& nums, int k) {
        // If I expand right and violate/satisfy the condition, does moving left have a predictable one-directional effect that lets me permanently discard possibilities?

        int count = 0;

        for (int l = 0; l < nums.size(); l++) {
            int sum = 0;
            for (int r = l; r < nums.size(); r++) {
                sum += nums[r];

                if (sum == k) count++;
            }
        }

        return count;
    }
    // divergences:
    // - initially brute forced O(n^3) because I looped the sum calculation

    // TC: O(n), SC: O(n)
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;

        unordered_map<int, int> freq;
        // sentinel value for prefix sum
        freq[0] = 1;

        int total = 0;

        for (int i = 0; i < nums.size(); i++) {
            total += nums[i];

            // we use prefix sum because `total - earlierPrefix = k ` => `earlierPrefix = total - k`
            // | earlier total  |  sums to k   |
            // |         current total         |

            // "Have I previously seen a prefix sum equal to the exact value I need so that subtracting it from my current sum gives k"
            if (freq.count(total - k)) {
                count += freq[total - k];
            }

            // log the current total as an earlier total
            freq[total]++;
        }

        return count;
    }
};
// divergences:
// - took a LONG time to understand the prefix sum part