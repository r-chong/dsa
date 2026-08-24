// Brute force
class Solution {
    pair<int, int> br;

    int pathsFrom(int i, int j) {
        if (i == br.first && j == br.second) return 1;

        // check if the indice we can move onto is valid
        // if so, compute
        int down = ((i + 1) <= br.first) ? pathsFrom(i + 1, j) : 0;
        int right = ((j + 1) <= br.second) ? pathsFrom(i, j + 1) : 0;

        return down + right;
    }
public:
    int uniquePaths(int m, int n) {
        br = {m - 1, n - 1};

        return pathsFrom(0, 0);
    }
};

// Top down DP
class Solution {
    pair<int, int> br;
    vector<vector<int>> memo;

    int pathsFrom(int i, int j) {
        if (i == br.first && j == br.second) return 1;
        if (memo[i][j] != -1) return memo[i][j];

        // check if the indice we can move onto is valid
        // if so, compute
        int down = ((i + 1) <= br.first) ? pathsFrom(i + 1, j) : 0;
        int right = ((j + 1) <= br.second) ? pathsFrom(i, j + 1) : 0;

        return memo[i][j] = down + right;
    }
public:
    int uniquePaths(int m, int n) {
        br = {m - 1, n - 1};

        memo = vector<vector<int>>(m, vector<int>(n, -1));

        return pathsFrom(0, 0);
    }
};
// divergences:
// - forgot syntax for updating global memo
// - didnt include br.first, br.second as valid indices, getting 0 always

// Bottom up dp iterative
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> memo(m, vector<int>(n, -1));

        memo[m - 1][n - 1] = 1;

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                // preserve base case
                if (i == m - 1 && j == n - 1) continue;

                int down = ((i + 1) <= m - 1) ? memo[i + 1][j] : 0;
                int right = ((j + 1) <= n - 1) ? memo[i][j + 1] : 0;

                memo[i][j] = down + right;
            }
        }

        return memo[0][0];
    }
};
// divergences:
// - did not include if (i == m - 1 && j == n - 1) continue; line, which meant I replaced base case and got 0