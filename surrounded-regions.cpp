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