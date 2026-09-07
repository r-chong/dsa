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

class Solution {
public:
    // TC: O(nlogk), SC: O(n)
    // multiset is balanced binary tree implementation, so n insertions * logn from binary tree insertion/deletion/search (all logn operations)
    // and size of tree is at most k (due to window size)
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int l = 0;
        int r = 0;

        vector<int> answer;
        multiset<int> window;
        
        while (r < nums.size()) {
            window.insert(nums[r]);

            // if r < k then we're growing still and should not update answer
            if (window.size() >= k) {
                auto max_val = *window.rbegin();
                answer.push_back(max_val);
                window.erase(window.find(nums[l]));
                l++;
            }
            r++;
        }

        return answer;
    }
};
// divergences:
// - didnt think of a multiset
// - growing case - off-by-one so was not pushing answer in all cases and not updating correctly

// exercise for next time: implement with heap w/ lazy deletion