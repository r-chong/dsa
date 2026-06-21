class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix[0].size();
        int n = matrix.size();
        int o = m * n;

        int l = 0;
        int r = o - 1;

        while (l <= r) {
            int i = l + (r - l) / 2;

            int row = i / m;
            int col = i % m;

            int curr = matrix[row][col];

            if (curr == target) {
                return true;
            } else if (curr > target) {
                r = i - 1;
            } else {
                l = i + 1;
            }
        }

        return false;
    }
    // divergences:
    // - didn't internalize indexing had to look up how to do it
    // - used a lot of variables
    // - didnt have <= in condition
    // - forgot divide by 2 overflow prevention


    bool searchMatrixPredicate(vector<vector<int>>& matrix, int target) {
        int n = matrix.size(); // ROWS
        int m = matrix[0].size(); // COLS

        int total = n * m;

        auto ok = [&](int i) {
            int row = i / m;
            int col = i % m;

            return matrix[row][col] >= target;
        };

        int lo = 0;
        int hi = total;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (ok(mid)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        // not found
        if (lo == total) {
            return false;
        }

        int row = lo / m;
        int col = lo % m;

        // found a greater value, is equal to target?
        return matrix[row][col] == target;
    }
};
// divergences 2:
// - used hi instead of lo as return value
// - forgot >= in predicate
// - returned true if found, which is wrong: predicate / loading bar binary search is not checking for equality, only for GEQ target.