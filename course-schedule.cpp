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
    // TC: O(n^2), SC: O(n^2) due to row having possibly n prerequisites. also n on call stack
    // n = numCourses
    // CORRECTION: use v+e for graphs, this is wrong
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


//REVIEW: GPT SOLUTION
class Solution {
    bool dfs(int curr, vector<int>& state, vector<vector<int>>& graph) {
        if (state[curr] == 1) return false; // cycle
        if (state[curr] == 2) return true;  // already verified

        state[curr] = 1;

        for (int nei : graph[curr]) {
            if (!dfs(nei, state, graph)) {
                return false;
            }
        }

        state[curr] = 2;
        return true;
    }

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);

        for (auto& p : prerequisites) {
            graph[p[0]].push_back(p[1]);
        }

        vector<int> state(numCourses, 0);

        for (int i = 0; i < numCourses; i++) {
            if (!dfs(i, state, graph)) {
                return false;
            }
        }

        return true;
    }
};