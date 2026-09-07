class Solution {
public:
    // TC: O(V+E), SC: O(V+E)
    // topological sort kahn's
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // create graph
        vector<vector<int>> graph(numCourses, vector<int>());

        for (vector<int>pair : prerequisites) {
            // a_i : b_i adjacency list
            graph[pair[1]].push_back(pair[0]);
        }

        vector<int> indegree(numCourses, 0);
        
        // count degree of each node
        for (int i = 0; i < numCourses; i++) {
            for (int prereq : graph[i]) {
                indegree[prereq]++;
            }
        }

        queue<int> q;
        // init the queue with 0 indegree nodes
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        int idx = 0;
        vector<int> topoSorted(numCourses, 0);

        // create topo ordering on the fly
        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            topoSorted[idx++] = curr;

            for (int next : graph[curr]) {
                indegree[next]--;

                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        // cycle detect logic
        if (idx != numCourses) {
            return {};
        }

        return topoSorted;
    }
};
// divergences:
// - swapped graph order since was thinking about Course Schedule I
// - had to learn Kahn's algorithm