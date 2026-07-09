class Solution {
public:
    // TC: O(n), SC: O(1)
    // does not match problem constraints
    int findMinV1(vector<int>& nums) {
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
// divergences:
// - i was doing some janky shit by thinking i needed to do more work
// - NVM i wasnt tweaking just no indexing needed

// while (l < r) {
        //     // indexing shift
        //     int newL = (l + pivot - 1) % pivot;
        //     int newR = (r + pivot - 1) % pivot;

        //     int mid = l + (l + r) / 2;

        //     if (nums[mid] < mini) {
        //         mini = nums[mid];
        //     }
        // }

    // TC: O(logn), SC: O(1)
    // optimal
    int findMin(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        
        int l = 0;
        int r = n - 1;
        while (l < r) {
            int mid = l + (r - l) / 2;

            if (nums[mid] > nums[r]) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }

        return nums[l];
    }
    // divergences:
    // - i thought i was comparing nums[mid] to nums[mid + 1] or something, not just the right side. but it makes sense, since we do have access to the lower/upper bounds.
    // - mid was wrong. l + (r - l) / 2 is correct.
    // - didnt know what to return
};