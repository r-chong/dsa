// Brute force solution
// TC: O(n^2), SC: O(1) 
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int maxWater = 0;

        // for all i, calculate max water above the bar (if theres a bar)
        for (int i = 0; i < n; i++) {
            int maxLeft = 0;
            int maxRight = 0;

            for (int l = i; l >= 0; l--) {
                maxLeft = max(height[l], maxLeft);
            }

            for (int r = i; r < n; r++) {
                maxRight = max(height[r], maxRight);
            }

            maxWater += min(maxLeft, maxRight) - height[i];
        }

        return maxWater;
    }
};

// maxLeft maxRight array solution
// TC: O(n), SC: O(n)
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int maxWater = 0;

        vector<int> maxLeft(n, 0);
        vector<int> maxRight(n, 0);

        maxLeft[0] = height[0];
        maxRight[n - 1] = height[n - 1];

        for (int l = 1; l < n; l++) {
            maxLeft[l] = max(height[l], maxLeft[l - 1]);
        }

        for (int r = n - 2; r >= 0; r--) {
            maxRight[r] = max(height[r], maxRight[r + 1]);
        }

        for (int i = 0; i < n; i++) {
            maxWater += min(maxLeft[i], maxRight[i]) - height[i];
        }

        return maxWater;
    }
};
// divergences:
// - assumed maxLeft and maxRight are 0
// - tried to do some fancy sentinel value stuff but messed up indexing