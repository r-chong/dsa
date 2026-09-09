class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int rows = board.size();
        int cols = board[0].size();

        // rows
        for (int r = 0; r < rows; ++r) {
            if (board[r][0] == 'O') {
                dfs(board, r, 0);
            }

            if (board[r][cols - 1] == 'O') {
                dfs(board, r, cols - 1);
            }
        }

        // cols
        for (int c = 0; c < cols; ++c) {
            if (board[0][c] == 'O') {
                dfs(board, 0, c);
            }

            if (board[rows - 1][c] == 'O') {
                dfs(board, rows - 1, c);
            }
        }

        // Find non-borders, and turn to X if not safe
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (board[r][c] == 'O') {
                    board[r][c] = 'X';
                } else if (board[r][c] == 'S') {
                    // already processed, so ensure that we change it back.
                    board[r][c] = 'O';
                }
            }
        }
    }

    void dfs(vector<vector<char>>& board, int x, int y) {
        int rows = board.size();
        int cols = board[0].size();

        // ensure that the current cell is O and is a valid coord, else disregard
        if (x < 0 || x >= rows || y < 0 || y >= cols) {
            return;
        }
        if (board[x][y] != 'O') {
            return;
        }

        // mark O's as safe.
        board[x][y] = 'S';

        // left and right
        dfs(board, x + 1, y);
        dfs(board, x - 1, y);
        dfs(board, x, y + 1);
        dfs(board, x, y - 1);
    }
};

class Solution {
    const int DIRS[4][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    void dfs(int sr, int sc, vector<vector<bool>>& visited, vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();

        visited[sr][sc] = true;

        // go to each neighbour
        for (auto& dir : DIRS) {
            int r = sr + dir[0];
            int c = sc + dir[1];

            // OOB
            if (r < 0 || c < 0 || r >= m || c >= n) {
                continue;
            }

            if (visited[r][c]) {
                continue;
            }

            if (board[r][c] == 'X') {
                continue;
            }

            dfs(r, c, visited, board);
        }
    }
    
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();

        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // if we traverse O regions starting from the edge of board, we KNOW there is an O on the edge
        // if we do not start at O we start at the middle, then middle parts must wait for information about an O being on the edge

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if ((r == 0 || r == m - 1 || c == 0 || c == n - 1) && board[r][c] == 'O') {
                    dfs(r, c, visited, board);
                }
            }
        }

        // traversing this gives us the O's which will remain and the rest are effectively gone
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (!visited[r][c]) {
                    board[r][c] = 'X';
                }
            }
        }
    }
};
// divergences:
// - trivial bug: put m in both r & c boundary check in dfs
// - syntax: wrote int[][] the brackets suppposed to go after the name
// - dir : DIRS - dir must be a reference
// - 