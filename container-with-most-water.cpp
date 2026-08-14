// TC: O(n^2), SC: O(1)
// Brute force
class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxA = 0;

        for (int i = 0; i < height.size(); i++) {
            for (int j = i; j < height.size(); j++) {
                int area = min(height[i], height[j]) * (j - i);

                maxA = max(maxA, area);
            }
        }

        return maxA;    
    }
};

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

class Solution {
public:
    // TC: O(n), SC: O(1)
    int maxArea(vector<int>& height) {
        int n = height.size();

        int maxA = 0;

        int l = 0;
        int r = n - 1;

        while (l < r) {
            int a = min(height[l], height[r]) * (r - l);

            maxA = max(maxA, a);

            if (height[l] >= height[r]) {
                r--;
            } else {
                l++;
            }
        }

        return maxA;
    }
};
// divergences:
// - fumbled variables a little at the start but

// convergences:
// - solved with brute force -> optimal in 8:48 without references or syntax errors.