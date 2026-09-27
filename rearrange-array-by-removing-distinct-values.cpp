class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        multiset<int> ms(nums.begin(), nums.end());
        vector<int> ans;

        int prev;
        while (!ms.empty()) {
            prev = 0;
            
            for (auto it = ms.begin(); it != ms.end(); ) {
                int x = *it;
                
                if (x != prev) {
                    it = ms.erase(it);
                    ans.push_back(x);
                } else {
                    ++it;
                }

                prev = x;
            }
        }

        return ans;
    }
};
// divergences:
// - initial intuition was messed up. see:

// class Solution {
// public:
//     vector<int> rearrangeArray(vector<int>& nums) {
//         vector<int> freq(101, 0);
//         vector<int> ans;

//         sort(nums.begin(), nums.end());

//         int m = 1;
//         for (int i = 0; i < nums.size(); i++) {
//             freq[nums[i]]++;

//             m = max(m, freq[nums[i]]);
//         }

//         for (int k = 1; k <= m; k++) {
//             for (int i = 0; i < nums.size(); i++) {
//                 if (freq[nums[i]] == k) {
//                     freq[nums[i]]--;
//                     ans.push_back(nums[i]);
//                 }
//             }
//         }

//         return ans;
//     }
// };©leetcode