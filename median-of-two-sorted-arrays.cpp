// O(m+n)
// TC: O(log(m+n)), SC: O(1)
// m = length of nums1, n = length of nums2
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> merged;

        merged.insert(merged.end(), nums1.begin(), nums1.end());
        merged.insert(merged.end(), nums2.begin(), nums2.end());

        sort(merged.begin(), merged.end());

        int n = merged.size();

        if (n % 2 == 0) {
            int mid2 = n / 2;
            int mid1 = mid2 - 1;

            return (static_cast<double>(merged[mid1]) +
                    static_cast<double>(merged[mid2])) / 2.0;
        }

        return static_cast<double>(merged[n / 2]);
    }
};
// divergences:
// - forgot double
// - forgot static_cast
// - forgot sort

// Brute forceg
// TC: O(nlog(m+n)), SC: O(m+n)
// m = length of nums1, n = length of nums2
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums2.size() < nums1.size()) {
            swap(nums1, nums2); // such that nums1 is the smaller one
        }

        int m = nums1.size();
        int n = nums2.size();

        int lo = 0;
        int hi = m;
       
        // binary search the smaller array because...
        while (lo <= hi) {
            // we are binary-searching one partition position, i, inside the smaller array
            // num elements taken from nums1
            int i = lo + (hi - lo) / 2;

            // num elements taken from nums2
            // js is dependent on i, we don't have two pointers
            int j = (m + n + 1) / 2 - i;

            // (i == 0) or (i == m) means it's the start
            // later: set left to INT_MIN and right to INT_MAX if its the start

            int left1  = (i == 0) ? INT_MIN : nums1[i - 1];
            int right1 = (i == m) ? INT_MAX : nums1[i];

            int left2  = (j == 0) ? INT_MIN : nums2[j - 1];
            int right2 = (j == n) ? INT_MAX : nums2[j];

            // success: both ranges are disjoint
            // if they cross over, we're not finished
            if (left1 <= right2 && left2 <= right1) {
                // odd case
                if ((m + n) % 2 == 1) {
                    return max(left1, left2);
                }
                
                return (
                    static_cast<double>(max(left1, left2)) +
                    static_cast<double>(min(right1, right2))
                ) / 2.0;
            }

            if (left1 > right2) {
                // Took too many elements from nums1.
                hi = i - 1;
            } else {
                // Took too few elements from nums1.
                lo = i + 1;
            }
        }

        return 0.0; // unreachable due to problem invariants
    }
};
// divergences:
// - didnt understand ternary operator reason
// - didnt understand success invariant