class Solution {
public:
    // TC: O(n^2), SC
    vector<int> maxSlidingWindowBruteForce(vector<int>& nums, int k) {
        vector<int> res;

        int n = nums.size();

        for (int i = 0; i <= n - k; i++) {
            int mx = nums[i];
            for (int j = i; j < i + k; j++){
                mx = max(mx, nums[j]);
            }
            res.push_back(mx);
        }

        return res;
    }
    
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> res;

        int n = nums.size();
        res.reserve(n - k + 1);

        for (int i = 0; i < n; i++) {
            // remove expired
            if (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }

            // remove items smaller than the added, since the added would "dominate" those as maxima anyway
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }

            dq.push_back(i);

            // add an answer for each window
            // note that we should build up the window (so dont add first k - 1 as maxima, wait till we hit end of first slidijng window) and go the end with indexing from rightmost part of window
            if (i >= k - 1) {
                res.push_back(nums[dq.front()]);
            }
        }

        return res;
    }
};
// divergences:
// - messed up indexing in brute force
// - wrote "isempty()"" instead of "empty()""
// - added answer at same time as dq push back

// AI: "Main correction: your old logic mixed two different interpretations of i.
// i <= n - k means “i is the window start.”
// i >= k - 1 means “i is the window end.”