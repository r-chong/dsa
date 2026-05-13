class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        // we can colour the graph such that starting from a node, put in set A 
        // its neighbours have to be in set B
        // each of those neighbours must be in set A
        // if any conflicts, then is not bipartite
        // else, bipartite. single nodes are ok
        vector<unordered_set<int>> p(2);
        int len = graph.size();
        unordered_set<int> visited;

        // actually we should run bfs over all nodes, not just one. there are orphans.
        queue<int> q;

        vector<int> color(n, -1); 
        // -1 = uncolored
        //  0 = group A
        //  1 = group B

        // LOOP OVER ALL NODES (each layer has its own)
        for (int a = 0; a < len; a++) {
            if (color[start] != -1) continue;

            // BFS INIT
            q.push(a);
            
            if (visited.count(a)) {
                // assume valid
                continue;
            }

            visited.insert(a);
            p[].insert(a);

            // BFS WHILE
            // as soon as we enter the while, we should not really reference a
            while(!q.empty()) {
                int curr = q.front();
                q.pop();

                // NEIGHBOURS
                for (int nei : graph[curr]) {
                    // the set needs to change per neighbour level
                    color[nei] = 1 - color[curr];

                    // validity
                    if (nei == curr) {
                        continue;
                    }

                    // if in MY set, NOT OK
                    if (p[].count(nei)) {
                        return false;
                    }

                    // PROCESS
                    q.push(nei);
                    visited.insert(nei);
                    p[].insert(nei);
                }           
            }
        }
        // if pass all those then we ok
        // orphans dont matter
        return true;
    }
};