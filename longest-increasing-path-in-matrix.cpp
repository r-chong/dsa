class Solution {
public:
    int dfs(vector<vector<int>>& matrix, int sr, int sc, vector<int> &dp) {
        int m = matrix.size();
        int n = matrix[0].size();

        int idx = sr * n + sc;

        if (dp[idx] != -1) {
            // already memoized
            return dp[idx];
        }

        // must check 4 directions
        // must validate those cells 
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // start the path HERE
        int best = 1;

        // for each neighbour (direction)
        // return 1 + longest path via dfs'ing
        for (auto [dr, dc] : dirs) {
            // candidate row, col
            int cr = sr + dr;
            int cc = sc + dc;

            // check validity
            if (cr < 0 || cr >= m || cc < 0 || cc >= n) {
                continue;
            }

            // increasing?
            if (matrix[cr][cc] <= matrix[sr][sc]) {
                continue;
            }

            // take neighbour with longest increasing path NOT including me
            // we only get here if it's a valid square AND increasing value

            // we're comparing against other candidates

            // best starts at 1 because thats default
            // must ensure that we account for adding 1 to the neighbours' longest paths too, since they don't count us
            best = max(best, 1 + dfs(matrix, cr, cc, dp));
        }

        dp[idx] = best;
        return best;
    }

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        // run dfs on each square
        // try to go as far as we can for each given square
        // save that as its longest increasing path (subproblem)
        // dynamic programming
        // array with m x n cells

        // we check depth of neighbours
        // starting cells' neighbours dont have any depth (their length is 1)
        // if your neighbours do have a depth, take the maximum one
        // and you shouldn't have to even traverse, just check the dp index
        // is there gonna be indexing issues? so just need to make directions (loop over k directions)

        // ----
        int m = matrix.size();
        int n = matrix[0].size();

        // -1 initialization as an indicator if already memoized
        vector<int> dp(m * n, -1);

        // for loop to loop over the matrix
        // launch dfs on each one just checking the highest neighbouring depth
        // we keep this for fast access of largest
        int longest = 1;
        
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                longest = max(longest, dfs(matrix, r, c, dp));
            }
        }

        return longest;
    }
};