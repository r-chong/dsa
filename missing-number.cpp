class Solution {
public:
    int missingNumber(vector<int>& nums) {
        // order does not matter
        int n = nums.size();
        int ans = n;

        // xor two sets: "exists" vs "needs"
        // they could be done in separate loops as well.
        for (int i = 0; i < n; i++) {
            ans ^= nums[i]; // <- exists
            ans ^= i;       // <- needs
        }

        return ans;
    }
};