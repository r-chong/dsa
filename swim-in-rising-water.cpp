class Solution {
public:
    // bfs measures the time for a path
    int bfs(vector<vector<int>> &grid, vector<vector<int>> &visited, int sr, int sc) {
        int rows = grid.size();
        int cols = grid[0].size();

        // height, row, col
        // since heights are unique, should never sort by row etc
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> heap;

        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        heap.push({grid[sr][sc], sr, sc});
        visited[sr][sc] = 1;

        int time = 0;
        while (!heap.empty()) {
            tuple<int, int, int> curr = heap.top();
            auto [height, curr_row, curr_col] = curr;

            // the next item to be popped in min heap is the new min time
            // however, we could also go down in time (so keep a max)
            heap.pop();
            time = max(time, height);

            if ((curr_row == (rows - 1)) && (curr_col == (cols - 1))) {
                return time;
            }

            for (auto [r, c] : dirs) {
                // add new coordinate candidate
                int cr = r + curr_row;
                int cc = c + curr_col;
                
                // validate in bounds
                if (cr < 0 || cr >= rows || cc < 0 || cc >= cols) {
                    continue;
                }

                // skip visited
                if (visited[cr][cc] == 1) {
                    continue;
                }
                
                // valid direction to pursue
                heap.push({grid[cr][cc], cr, cc});
                visited[cr][cc] = 1;
            }
        }

        return time;
    }

    int swimInWater(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        vector<vector<int>> visited(rows, vector<int>(cols, 0));;

        return bfs(grid, visited, 0, 0);
    }
};

// divergences:
// I had to move the checker for isBottomRight. I was checking during neighbour but should have evaluated at curr
// I think time isn't up to date if I check in neighbours?