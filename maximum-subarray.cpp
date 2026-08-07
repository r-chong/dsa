class Solution {
public:
    int maxSubArrayBruteForce(vector<int>& nums) {
        int current = 0;
        int best = nums[0];

        for (int i = 0; i < nums.size(); i++) {
            for (int j = i; j < nums.size(); j++) {
                current += nums[j];

                best = max(best, current);
            }

            current = 0;
        }

        return best;
    }

    // Kadane's: start new streak OR continue previous

    // TC: O(n), SC: O(1)
    // n = size of nums
    // each node is processed once
    int maxSubArrayKadanes(vector<int>& nums) {
        int current = 0;
        int best = nums[0];

        for (int i = 0; i < nums.size(); i++) {
            current += nums[i];

            if (current < nums[i]) {
                current = nums[i];
            }

            best = max(best, current);
        }

        return best;
    }
};
// divergences:
// - didn't know Kadane's algorithm
// - set best as 0 when it should have started at nums[0] (edge case for nums.size() == 1)