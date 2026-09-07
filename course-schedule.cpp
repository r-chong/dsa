class Solution {
    // true if valid path
    // false if there is a cycle
    bool dfs(int curr, vector<bool>& visiting, vector<bool>& visited, vector<vector<int>>& graph) {
        if (visited[curr]) return true;
        if (visiting[curr]) return false;

        visiting[curr] = true;

        // visit all neighbours
        bool allValid = true;
        for (int nei : graph[curr]) {
            bool result = dfs(nei, visiting, visited, graph);
            cout << result << " for " << nei << "\n";
            allValid = allValid && result;
        }

        if (allValid) {
            visited[curr] = true;
        }

        return allValid;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses, vector<int>());

        for (int i = 0; i < prerequisites.size(); i++) {
            // a : push back b
            graph[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }

        // contains verified courses
        vector<bool> visited(numCourses, false);
        // current path of one course

        bool allValid = true;
        for (int i = 0; i < numCourses; i++) {
            vector<bool> visiting(numCourses, false);
            allValid = allValid && dfs(i, visiting, visited, graph);
        }

        return allValid;
    }
};
// divergences:
// - was not short circuiting true to already visited/verified nodes
// - was checking visiting[curr] before visited[curr] so one interconnected course meant that visiting had a "cycle" even though it was already verified. solution was just to check visited[curr] first.