// so the idea of this problem is reverse multi-source BFS
// and if you run bfs multiple times even if iterative, it makes more sense to create a function
class Solution {
    const int DIRS[4][2] = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    
    // TC: O(V+E), SC: O(V)
    // v = vertexes (coordinates)
    // e = edges (up down left right)
    void bfs(queue<pair<int, int>>& q, vector<vector<bool>>& visited, vector<vector<int>>& heights) {
        int m = heights.size(); // rows
        int n = heights[0].size(); // cols

        while (!q.empty()) {
            auto [sr, sc] = q.front();
            q.pop();

            // try flowing to neighbours
            for (int k = 0; k < 4; k++) {
                // candidate r,c
                int cr = sr + DIRS[k][0];
                int cc = sc + DIRS[k][1];

                if (cr >= m || cc >= n || cr < 0 || cc < 0) {
                    continue;
                }

                if (visited[cr][cc]) {
                    continue;
                }

                if (heights[cr][cc] < heights[sr][sc]) {
                    continue;
                }

                q.push({cr, cc});
                visited[cr][cc] = true;
            }
        }
    }
public:
    // TC: O(2*m*n) == O(m*n), SC: O(m*n)
    // we run BFS on at most every coord in the grid, drop constant 2 (if there were k oceans it would be kmn)
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size(); // rows
        int n = heights[0].size(); // cols

        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));

        // init queue for atlantic
        queue<pair<int, int>> pacQ;
        queue<pair<int, int>> atlQ;
        
        // xxxx
        // x
        // x
        
        // row 0
        for (int i = 0; i < n; i++) {
            pacQ.push({0, i});
            pacific[0][i] = true;
        }

        // col 0
        for (int i = 0; i < m; i++) {
            pacQ.push({i, 0});
            pacific[i][0] = true;
        }

        //    x
        //    x
        // xxxx

        // row m - 1
        for (int i = 0; i < n; i++) {
            atlQ.push({m - 1, i});
            atlantic[m - 1][i] = true;
        }

        // col n - 1
        for (int i = 0; i < m; i++) {
            atlQ.push({i, n - 1});
            atlantic[i][n - 1] = true;
        }

        bfs(pacQ, pacific, heights);
        bfs(atlQ, atlantic, heights);

        vector<vector<int>> answer;

        // loop over visited for each and add coordinate pair i,j to answer if BOTH are true
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (pacific[r][c] && atlantic[r][c]) {
                    answer.push_back({r, c});
                }
            }
        }

        return answer;
    }
};
// divergences:
// - need more granular
// - had repeated mixups with r, c
// - DIRS had to check answer for syntax

// i need to basically memorize* (be able to rederive bfs) on any problem same with dfs so not that i need copy paste sol but I need the key parts to be automatic in my head
// moreover i need to get used to r,c DIRS setups 