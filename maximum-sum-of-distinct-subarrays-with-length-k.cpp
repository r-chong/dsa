class Solution {
public:
    // brute force
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long best = 0;

        for (int l = 0; l + k <= nums.size(); l++) {
            long long sum = 0;
            unordered_set<int> seen;

            for (int r = l; r < l + k; r++) {
                sum += nums[r];
                seen.insert(nums[r]);
            }

            if (seen.size() == k) {
                best = max(best, sum);
            }
        }

        return best;
    }
    // divergences:
    // - forgot long long
    // - the + k should be part of for loop conditional

    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long best = 0;
        long long sum = 0;
        unordered_map<int, int> seen;

        int duplicates = 0;
        for (int r = 0; r < nums.size(); r++) {      
            // trick to catch the exact transition to there being duplicates. 
            sum += nums[r];
            if (++seen[nums[r]] == 2) {
                duplicates++;
            }

            // do not remove when building up r 
            // remove left side, left is derived using fixed window
            if (r > k - 1) {
                sum -= nums[r - k];
                if (--seen[nums[r - k]] == 1) {
                    duplicates--;
                }
            }

            // valid
            if (r >= k - 1 && duplicates == 0) {
                best = max(best, sum);
            }
            cout << best << endl;
        }

        return best;
    }
};
// divergences:
// - DO NOT DO THIS - I did ++seen[nums[r]] > 1 as frequency of 2 == frequency of 3 so we'd have double duplicate for the same entry
// - indexing: missed the first window in valid condition
// - forgot long long in sum
// - seen semantics
// - can remove l
