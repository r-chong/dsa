// TC: O(n), SC: O(1)
class Solution {
public:
    int maxArea(vector<int>& height) {
        int res = 0;

        int l = 0;
        int r = height.size() - 1;
        while (l < r) {
            int h = min(height[l], height[r]);
            int w = r - l;

            res = max(res, w * h);

            if (height[l] == height[r]) {
                l++;
                r--;
            } else if (height[l] < height[r]) {
                l++;
            } else {
                r--;
            }
        }

        return res;
    }
};
// noticed width starts large and only shrinks :)
// had the right skipping idea
// this was a good solve