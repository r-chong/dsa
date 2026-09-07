// return type logic:
// void = "go do traversal work."
// non-void = "go compute something and give it back to me."

void dfs(
    int r,
    int c,
    vector<vector<bool>>& visited,
    vector<vector<int>>& heights
) {
    int m = heights.size();
    int n = heights[0].size();

    visited[r][c] = true;

    for (auto& dir : DIRS) {
        int nr = r + dir[0];
        int nc = c + dir[1];

        if (nr < 0 || nr >= m || nc < 0 || nc >= n)
            continue;

        if (visited[nr][nc])
            continue;

        // problem-specific condition

        dfs(nr, nc, visited, heights);
    }
}