// For graphs

// Can either put inside
// void bfs(sr, sc, q, visited, graph)
// or use directly within main

int dirs[4][2] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};

while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop();

    for (auto& dir : dirs) {
        int nr = r + dir[0];
        int nc = c + dir[1];

        if (nr < 0 || nr >= m || nc < 0 || nc >= n)
            continue;

        if (visited[nr][nc])
            continue;

        // problem-specific condition here

        visited[nr][nc] = true;
        q.push({nr, nc});
    }
}