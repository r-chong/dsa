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
// TC: typically for grid O(n*m), SC: O(1) 
// however, for standard Sudoku, both are still O(1) because the board size is fixed.
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<int> rows(9, 0);
        vector<int> cols(9, 0);
        vector<int> squares(9, 0);

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == '.') {
                    continue;
                } else {
                    int x = board[i][j] - '0' - 1;

                    if (rows[i] & (1 << x)) return false;
                    rows[i] |= (1 << x);

                    int square_idx = (i / 3) * 3 + (j / 3);
                    if (squares[square_idx] & (1 << x))return false;
                    squares[square_idx] |= (1 << x);

                    if (cols[j] & (1 << x)) return false;
                    cols[j] |= (1 << x);
                }
            }
        }
        return true;
    }
};

// divergences
// - used logical AND not bitwise AND
// - updated the index in the board not the actual variable
// - created one mask for all rows
// - didn't translate 2d indices to bitmask (was using i instead of j for cols)


// BONUS:
// you can further optimize by:
// - use array instead of vector

// ```
// array<int, 9> rows{};
// array<int, 9> cols{};
// array<int, 9> boxes{};
// ```

// - use uint16_t instead of int
// these don't require changes to the bitmask code.

#include <array>

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        array<uint16_t, 9> rows{};
        array<uint16_t, 9> cols{};
        array<uint16_t, 9> squares{};

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == '.') {
                    continue;
                } else {
                    int x = board[i][j] - '0' - 1;

                    if (rows[i] & (1 << x)) return false;
                    rows[i] |= (1 << x);

                    int square_idx = (i / 3) * 3 + (j / 3);
                    if (squares[square_idx] & (1 << x))return false;
                    squares[square_idx] |= (1 << x);

                    if (cols[j] & (1 << x)) return false;
                    cols[j] |= (1 << x);
                }
            }
        }
        return true;
    }
};
