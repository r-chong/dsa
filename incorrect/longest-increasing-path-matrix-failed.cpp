class Solution {
public:
    int dfs(vector<vector<int>>& matrix, int sr, int sc, vector<int> &dp) {
        int m = matrix.size();
        int n = matrix[0].size();

        // 3 4 5
        // 3 2 6
        // 2 2 1

        // expected DP but we only max out at 2
        // 2 3 4
        // 1 4 1
        // 2 1 2

        // must check 4 directions
        // must validate those cells 
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        int max_neighbour = 0;

        // for each neighbour (direction)
        // return 1 + longest path via dfs'ing
        for (int k = 0; k < 4; k++) {
            auto [dr, dc] = dirs[k];

            // candidate row, col
            int cr = sr + dr;
            int cc = sc + dc;

            // check validity
            if (cr < 0 || cr >= m || cc < 0 || cc >= n) {
                continue;
            }

            // increasing?
            if (!(matrix[cr][cc] > matrix[sr][sc])) {
                continue;
            }

            // take neighbour with longest increasing path NOT including me

            // we only get here if it's a valid square AND increasing value

            // we're comparing against other candidates
            max_neighbour = max(dp[(cr * n) + cc], dp[(sr * n) + sc]);
        }

        // neighbours never count us, that's why we can add
        dp[(sr * n) + sc] += max_neighbour;

        // now we should be counted
        return dp[(sr * n) + sc];
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
        vector<int> dp(m * n, 1);

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

// Divergences:
// Base is inside the dfs not outside
// Ensure you use candidate neighbours in the recursion not self
// syntax error with the dirs. do {{},{}}
// and its easy to do auto [dr, dc] : dirs
