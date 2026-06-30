class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();

        // product of everything to left
        vector<int> pre(n + 1, 1);

        // product of everything to right
        vector<int> post(n + 1, 1);

        // pre: [s] ...
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] * nums[i];
        }

        // post: ... [s]
        for (int i = n - 1; i >= 0; i--) {
            post[i] = post[i + 1] * nums[i];
        }

        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = pre[i] * post[i + 1];
        }

        return ans;
    }
};
// divergences:
// - indexing. i need to review what I did to fix this. I'm basically randomly changing things