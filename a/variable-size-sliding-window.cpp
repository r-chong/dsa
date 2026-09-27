class Solution {
public:
    int maxSubarray(vector<int>& nums) {
        int l = 0;
        int ans = 0;

        vector<int> freq(501, 0);

        for (int r = 0; r < nums.size(); r++) {
            freq[nums[r]]++;

            while (/* current window is invalid */) {
                freq[nums[l]]--;
                l++;
            }

            ans = max(ans, r - l + 1);
        }

        return ans;
    }
};