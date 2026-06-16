// DFS cycle detection solution
// TC: O(n^2), SC: O(v+e)
class DFSSolution {
public:
    // dfs returns if there exists a path from curr to target
    bool dfs(int curr, int target, unordered_map<int, vector<int>>&graph, unordered_set<int>&visited) {
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

// TC: O(n), SC: O(n)
// technically TC is O(n α(n)), which is the inverse Ackermann function. it grows slowly so we effectively have O(n)
class DSUSolution {
private:
    class DSU {
        std::vector<int> parents;
        std::vector<int> size;
        int num_components;
            
        public:

        DSU(int n) {
            this->parents.resize(n);
            this->size.resize(n);
            this->num_components = n;

            for (int i = 0; i < this->parents.size(); i++) {
                this->parents[i] = i;
            }

            std::fill(this->size.begin(), this->size.end(), 1);
        }

        // Given a node 'a', find the root of the associated connected component.
        // Note that parents[a] is the next node upwards, not the final root.
        // We know a node is the final root if: it is equal to its parent.
        int find(int a) {
            // Path compression optimization: instead of read-only loop traversal,
            // update each node in component to point to its root.
            if (this->parents[a] != a) {
                this->parents[a] = find(this->parents[a]);
            }

            return this->parents[a];
        }

        // Merge the roots of two nodes 'a' and 'b'.
        // Note: union is a restricted keyword in C++
        bool unite(int a, int b) {
            int root_a = find(a);
            int root_b = find(b);

            if (root_a == root_b) return false;

            // Merge to larger size. We update the root, not a or b.
            // We don't care about updating the size index of the smaller component
            // as that index is no longer a root.
            if (this->size[root_a] < this->size[root_b]) {
                std::swap(root_a, root_b);
            } 

            this->parents[root_b] = root_a;
            this->size[root_a] += this->size[root_b];

            this->num_components--;

            return true;
        }

        // Given nodes 'a' and 'b' return if they are in the same connected component.
        bool connected(int a, int b) {
            int root_a = find(a);
            int root_b = find(b);

            return root_a == root_b;
        }

        // return total number of connected components.
        int count() {
            return this->num_components;
        }
    };

public:
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
        Solution::DSU dsu(n + 1);

        for (auto &edge : edges) {
            int ai = edge[0] - 1;
            int bi = edge[1] - 1;

            if (!dsu.unite(ai, bi)) {
                return edge;
            }
        }

        return {}; // unreachable under problem constraints
    }
};
// divergences:
// The problem labels nodes from 1 to n. DSU itself can be 0-indexed or 1-indexed. In this problem, edges.size() equals the number of nodes because the input
// is a tree with one extra edge: original tree had n - 1 edges, now it has n. 
// This is problem-specific. so edges.size() is not the number of nodes. don't take it as dogma

// If we subtract 1 from labels, DSU(n) is enough.
// If we keep labels as-is, use DSU(n + 1).