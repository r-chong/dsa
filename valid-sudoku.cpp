// TC: typically for grid O(n*m), SC: O(n*m) however both are O(1) as board size is fixed.
// n = number of rows
// m = number of cols
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<bool>> rows(9, vector<bool>(9, false));
        vector<vector<bool>> cols(9, vector<bool>(9, false));
        vector<vector<bool>> squares(9, vector<bool>(9, false));        

        // go through all elements of row
        // if already in array, then return false
        // otherwise add to array
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == '.') {
                    continue;
                } else {
                    int x = board[i][j] - '0' - 1;

                    if (rows[i][x]) {
                        return false;
                    }
                    rows[i][x] = true;

                    int square_idx = (i / 3) * 3 + (j / 3);
                    if (squares[square_idx][x]) {
                        return false;
                    }
                    squares[square_idx][x] = true;

                    if (cols[x][j]) {
                        return false;
                    }
                    cols[x][j] = true;
                }
            }
        }
        return true;
    }
};
// divergences
// - indexing, especially for squares
// - should always use enumeration for these types of problems, not range based for loops

// CHALLENGE: do with bitmask