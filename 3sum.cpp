// TC: O(n^2 log k), SC: O(k)
// k = number of unique triplets found
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        set<vector<int>> triplets;

        sort(nums.begin(), nums.end());

        // f for fixed. it's actually more left than the left
        for (int f = 0; f < n; f++) {
            int l = f + 1;
            int r = n - 1;

            while (l < r) {
                int sum = nums[f] + nums[l] + nums[r];

                if (sum == 0) {
                    vector<int> t({nums[f], nums[l], nums[r]});
                    triplets.insert(t);
                    l++;
                    r--;
                } else if (sum < 0) {
                    l++;
                } else {
                    r--;
                }
            }
        }

        vector<vector<int>> res;
        for (vector<int> t : triplets) {
            res.push_back(t);
        }

        return res;
    }
};
// divergences:
// - couldn't figure out how I wanted to fix indices
// - was unsure about sorting. it is necessary
// - forgot to increment/decrement l,r in the sum == 0 case, causing infinite loop
// - got while condition wrong. it is not based on f. f should be ignored

// TC: O(n^2), SC: O(1)
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;

        sort(nums.begin(), nums.end());

        // f for fixed. it's actually more left than the left
        for (int f = 0; f < n; f++) {
            // Skip duplicate fixed values
            if (f > 0 && nums[f] == nums[f - 1]) {
                continue;
            }

            int l = f + 1;
            int r = n - 1;

            while (l < r) {
                int sum = nums[f] + nums[l] + nums[r];

                if (sum == 0) {
                    res.push_back({nums[f], nums[l], nums[r]});                    

                    l++;
                    r--;

                    // skip duplicate left values
                    while (l < r && nums[l] == nums[l - 1]) {
                        l++;
                    }

                    // skip duplicate right values
                    while (l < r && nums[r] == nums[r + 1]) {
                        r--;
                    }
                } else if (sum < 0) {
                    l++;
                } else {
                    r--;
                }
            }
        }
        return res;
    }
};
// divergences: 
// - skip duplicate right values went the wrong way