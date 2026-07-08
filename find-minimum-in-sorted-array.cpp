class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        int shift = 0;

        for (int i = 1; i < nums.size(); i++) {
            // pass if nums[i] > nums[i - 1]
            if (nums[i] <= nums[i - 1]) {
                shift = i;
            }
        }

        return nums[shift];
    }
};
// divergences:
// - i was doing some janky shit by thinking i needed to do more work

// while (l < r) {
        //     // indexing shift
        //     int newL = (l + pivot - 1) % pivot;
        //     int newR = (r + pivot - 1) % pivot;

        //     int mid = l + (l + r) / 2;

        //     if (nums[mid] < mini) {
        //         mini = nums[mid];
        //     }
        // }