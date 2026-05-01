class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        bool has_fresh = false;

        int rows = grid.size();
        int cols = grid[0].size();
        int mins = 0;
        int num_sources = 0;
        
        std::vector<int> dr{-1, 1, 0, 0};
        std::vector<int> dc{0, 0, -1, 1};

        std::queue<pair<int, int>> q;

        // add multi sources (rotten oranges)
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 2) {
                    q.push({r, c});
                    num_sources++;
                }
            }
        }

        while(!q.empty()) {
            int cur = q.size();

            for (int i = 0; i < cur; i++) {
                auto [r, c] = q.front();
                q.pop();

                // adding neighbours
                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    // check constraints
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
                        continue;
                    }                    

                    // is it a fresh orange
                    if (grid[nr][nc] != 1) {
                        continue;
                    }

                    q.push({nr, nc});
                    grid[nr][nc] = 2;
                }
            }
            mins++;
        }

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1) {
                    has_fresh = true;
                }
            }
        }
        
        if (has_fresh) {
            return -1;
        } else if (num_sources == 0) {
            return 0;
        }else {
            return mins - 1;
        }
    }
};