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

// using boolean and editing grid directly
class Solution {
    vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    void bfs(int sr, int sc, vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        std::queue<pair<int, int>> q;
        q.push({sr, sc});

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++) {
                int cr = r + dirs[k][0];
                int cc = c + dirs[k][1];

                if (cr < 0 || cc < 0 || cr >= m || cc >= n) {
                    continue;
                }

                if (grid[cr][cc] == '0') {
                    continue;
                }

                // we may not short circuit as we need to visit all parts of this island.
                q.push({cr, cc});
                grid[cr][cc] = '0';
            }
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int islands = 0;

        // launch all coordinates
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == '1') {
                    islands++;
                    bfs(r, c, grid);
                }
            }
        }

        return islands;
    }
};
// divergences:
// - push and not push_back for q
// - pushed a grid item instead of pair
// - compared string but each grid item is chars

// using boolean and visited set
class Solution {
    vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    void bfs(int sr, int sc, vector<vector<char>>& grid, vector<vector<bool>> &visited) {
        int m = grid.size();
        int n = grid[0].size();
        
        std::queue<pair<int, int>> q;
        visited[sr][sc] = true;
        q.push({sr, sc});

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++) {
                int cr = r + dirs[k][0];
                int cc = c + dirs[k][1];

                if (cr < 0 || cc < 0 || cr >= m || cc >= n) {
                    continue;
                }

                if (grid[cr][cc] == '0') {
                    continue;
                }

                if (visited[cr][cc]) {
                    continue;
                }

                // we may not short circuit as we need to visit all parts of this island.
                q.push({cr, cc});
                visited[cr][cc] = true;
            }
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int islands = 0;
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // launch all coordinates
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == '1' && !visited[r][c]) {
                    islands++;
                    bfs(r, c, grid, visited);
                }
            }
        }

        return islands;
    }
};
// divergences:
// - push and not push_back for q
// - pushed a grid item instead of pair
// - compared string but each grid item is chars
// - detect land at root level and simply use bfs for flood fill

// for visited set
// - for 2d grid must initialize <vector<vector>> both vectors
// - add visited to:
//      - at queue creation
//      - invalidity
//      - valid