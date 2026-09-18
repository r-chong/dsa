class Solution {
    int n;
    int k;
    vector<vector<vector<__int128>>> memo;

    __int128 dp(int movesMade, int row, int column) {
        if (row < 0 || row >= n || column < 0 || column >= n) return 0;
        if (movesMade == k) return 1;
        if (memo[movesMade][row][column] != -1) return memo[movesMade][row][column];
        
        // check all neighbours, find a count of valid squares using recurrence
        return memo[movesMade][row][column] = 
            dp(movesMade + 1, row - 2, column + 1) +
            dp(movesMade + 1, row - 2, column - 1) +
            dp(movesMade + 1, row - 1, column + 2) +
            dp(movesMade + 1, row - 1, column - 2) +
            dp(movesMade + 1, row + 1, column + 2) +
            dp(movesMade + 1, row + 1, column - 2) +
            dp(movesMade + 1, row + 2, column + 1) +
            dp(movesMade + 1, row + 2, column - 1);
        }
public:
    double knightProbability(int n, int k, int row, int column) {
        this->n = n;
        this->k = k;

        memo = vector<vector<vector<__int128>>>(k, vector<vector<__int128>>(n, vector<__int128>(n, -1)));
        __int128 validAfterK = dp(0, row, column);
        
        return static_cast<double>(validAfterK) / std::pow(8.0, k);
    }
};
// divergences:
// - treated this as optimal search instead of path-sum
// - need to work on thinking on the recurrence more
// - in terms of memoization initialization, it should go 3vec 2vec 1vec and dont forget brackets
// - ran into signed integer overflow. even going to __int128 which I wouldn't have thought of in interview, runs into runtime error. Therefore, I need to detect that I should be dealing with probability throughout