class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        int count = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    count++;
                    bfs(grid, r, c);
                }
            }
        }

        return count;
    }

    void bfs(vector<vector<char>>& grid, int sr, int sc) {
        int rows = grid.size();
        int cols = grid[0].size();

        // direction arrays
        int dr[4] = {-1 ,1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        std::queue<pair<int, int>> q;
        q.push({sr, sc});
        grid[sr][sc] = '0';

        // add all of the neighbours to the queue
        while (!q.empty()) {
            // use auto to extract int
            auto [r, c] = q.front();
            q.pop();

            for (int k = 0; k < 4; ++k) {
                // find neighbours
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
                    continue;
                }
                
                if (grid[nr][nc] != '1') {
                    continue;
                }

                grid[nr][nc] = '0';
                q.push({nr, nc});
            }
        }
    }
};