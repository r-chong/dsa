class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        // we can colour the graph such that starting from a node, put in set A 
        // its neighbours have to be in set B
        // each of those neighbours must be in set A
        // if any conflicts, then is not bipartite
        // else, bipartite. single nodes are ok
        int n = graph.size();
        vector<int> colour(n, -1); 
        // use as visited as well

        // -1 = uncolored
        //  0 = group A
        //  1 = group B

        // LOOP OVER ALL NODES (each layer has its own)
        for (int a = 0; a < n; a++) {
            // visited equivalent
            if (colour[a] != -1) continue;

            // BFS INIT
            queue<int> q;
            q.push(a);
            colour[a] = 0;

            // BFS WHILE
            // as soon as we enter the while, we should not really reference a
            while(!q.empty()) {
                int curr = q.front();
                q.pop();

                // NEIGHBOURS
                for (int nei : graph[curr]) {
                    // the set needs to change per neighbour level
                    // validity
                    if (nei == curr) {
                        // SELF LOOP DIDNT THINK OF THAT
                        return false;
                    }

                    if (colour[nei] == -1) {
                        colour[nei] = 1 - colour[curr];
                        q.push(nei);
                    } else if (colour[nei] == colour[curr]) {
                        // if in MY set, NOT OK
                        return false;
                    }
                }           
            }
        }
        // if pass all those then we ok
        // orphans dont matter
        return true;
    }
};