class Solution {
public:
    const int INF = 2147483647;

    void wallsAndGates(vector<vector<int>>& rooms) {
        int rows = rooms.size();
        int cols = rooms[0].size();

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        std::queue<pair<int, int>> q;
        int dist = 0;

        std::vector<int> dr{-1, 1, 0, 0};
        std::vector<int> dc{0, 0, 1, -1};

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (rooms[r][c] == 0) {
                    q.push({r, c});
                    visited[r][c] = true;
                }
            }
        }

        while(!q.empty()) {
            int layerSize = q.size();

            for (int i = 0; i < layerSize; i++) {
                auto [r, c] = q.front();
                q.pop();

                // neighbours
                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    // constraints
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
                        continue;
                    }

                    if (visited[nr][nc] == true) {
                        continue;
                    }

                    // not a room
                    if (rooms[nr][nc] != INF) {
                        continue;
                    }

                    // previous cell already has shortest distance, so just add 1
                    rooms[nr][nc] = rooms[r][c] + 1;
                    q.push({nr, nc});
                }
            }

            dist++;
        }
    }
};