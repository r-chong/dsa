class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        // sentinel
        heights.push_back(0);

        std::vector<int> msi;
        int max = 0;

        for (int i = 0; i < heights.size(); ++i) {
            while (!msi.empty() && heights[i] < heights[msi.back()]) {
                int height_i = msi.back();
                msi.pop_back();

                int left_i = msi.empty() ? -1 : msi.back();
                int h = heights[height_i];
                int w = i - left_i - 1;

                max = std::max(max, h * w);
            }

            msi.push_back(i);
        }

        heights.pop_back();

        return max;
    }
};