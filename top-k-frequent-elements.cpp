// TC: O(n), SC: O(n)
// n = # of nums
// m = # unique elements
// m <= n
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // create buckets for frequency
        // add each value to the corresponding bucket (shift)
        // traverse buckets from end to beginning
        
        // we can at most have a frequency of nums.size();
        int n = nums.size();

        // element : freq bucket
        unordered_map<int, int> freq;

        // freq bucket : list of elements
        vector<vector<int>> buckets(n);
        
        for (int n : nums) {
            freq[n]++;
        }

        for (auto& it : freq) {
            buckets[it.second - 1].push_back(it.first);
        }

        vector<int> ans;

        for (int i = 0; i < buckets.size(); i++) {
            for (int b : buckets[n - i - 1]) {
                cout << b << endl;
            }
        }

        // # elements returned
        int e = 0; 

        for (int i = 0; i < buckets.size(); i++) {
            int idx = buckets.size() - i - 1;
            
            if (buckets[idx].empty()) {
                continue;
            };

            for (int n : buckets[idx]) {
                if (e == k) {
                    break;
                }

                ans.push_back(n);
                e++;
            }
        }

        return ans;
    }
};
// divergences:
// - changed loop type multiple times unnecessarily
// - not enough variables (needed e)
// - put unordered map inside buckets (not necessary)

// good:
// - console logging was helpful