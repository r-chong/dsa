class Solution {
public:
    // DFS cycle detection solution

    // dfs returns if there exists a path from curr to target
    bool dfs(int curr, int target, unordered_map<int, vector<int>>&graph, unordered_set<int>visited) {
        if (curr == target) {
            return true;
        }

        // visited tracks intermediary nodes to ensure no loop
        visited.insert(curr);

        for (int nei : graph[curr]) {
            if (!visited.count(nei)) {
                if (dfs(nei, target, graph, visited)) {
                    return true;
                };
            }
        }

        // no existing path
        return false;
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        unordered_map<int, vector<int>> graph;

        for (auto &edge : edges) {
            int ai = edge[0];
            int bi = edge[1];

            // Nodes I have already explored while trying to find v from u. Must reset
            unordered_set<int> visited;

            // This is the logic that actually prevents us from having two paths
            if (graph.count(ai) && graph.count(bi) && dfs(ai, bi, graph, visited)) {
                return edge;
            }

            // ONLY add to graph if it doesn't create a cycle
            graph[ai].push_back(bi);
            graph[bi].push_back(ai);
        }

        return {}; // unreachable under problem constraints
    }
};

// divergences:
// - wasnt sure how to proceed after creating the graph.. turns out this problem you process BEFORE adding to the graph.
// The graph is then available to the next iteration, but the main idea is that we validate if a edge is worth adding
// prior to adding it (therefore preventing cycle)
// - Returned DFS too early, I got the recursion but I returned it instead of putting it into the if statement.