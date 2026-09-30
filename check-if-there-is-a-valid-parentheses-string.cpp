class Solution {
    int M;
    int N;

    bool dfs(int i, int j, vector<int>& stack, vector<vector<char>>& grid) {
        if (i >= M) return false;
        if (j >= N) return false;

        bool pop = !stack.empty() && stack.back() == '(' && grid[i][j] == ')';
        if (pop) {
            stack.pop_back();
        } else {
            stack.push_back(grid[i][j]);
        }
        
        // valid found
        bool ans = false;
        if (i == M - 1 && j == N - 1) {
            ans = stack.empty();
        } else {
            ans = dfs(i + 1, j, stack, grid) || dfs(i, j + 1, stack, grid);
        }

        if (pop) {
            stack.push_back('(');
        } else {
            stack.pop_back();
        }

        return ans;
    }
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        M = grid.size();
        N = grid[0].size();

        vector<int> stack;

        return dfs(0, 0, stack, grid);
    }
};
// divergences:
// - misplaced the "found" base case it should not be at the top
// - didnt backtrack correctly
// - used .top() on vector