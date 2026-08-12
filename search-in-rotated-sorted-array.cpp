class Solution {
    // O(logn), SC: O(1)
    int findPivotIndex(vector<int>& nums) {
        int n = nums.size();

        int lo = 0;
        int hi = n - 1;

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (nums[mid] > nums[hi]) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        
        return lo;
    }
public:
    // TC: O(logn), SC: O(1)
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int pivot = findPivotIndex(nums);

        cout << pivot << endl;

        int lo = 0;
        int hi = n - 1;

        while (lo < hi) {
            // Mid represents the pointer covering the distance from lowest to target
            int mid = lo + (hi - lo) / 2;
            int realMid = (mid + pivot) % n;

            if (nums[realMid] < target) {
                lo = mid + 1;
            } else {
                // Maybe target is what we are looking for. Then, the loop should break
                hi = mid;
            }
        }

        int realIndex = (lo + pivot) % n;

        if (nums[realIndex] == target) {
            return realIndex;
        }

        return -1;
    }
};