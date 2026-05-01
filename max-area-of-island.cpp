class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        int max = 0;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1) {
                    max = std::max(max, bfs(grid, r, c));
                }
            }
        }

        return max;
    }

    int bfs(vector<vector<int>>& grid, int sr, int sc) {
        int rows = grid.size();
        int cols = grid[0].size();

        int area = 1;
        std::queue<pair<int, int>> q;
        q.push({sr, sc});
        grid[sr][sc] = 0;

        std::vector<int> dr = {-1, 1, 0, 0};
        std::vector<int> dc = {0, 0, -1, 1};

        while(!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                // check validity
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
                    continue;
                }

                if (grid[nr][nc] != 1) {
                    continue;
                }

                // mark it
                grid[nr][nc] = 0;
                area += 1;

                // push to queue
                q.push({nr, nc});
            }
        }

        return area;
    }
};