class Solution {
    vector<int> parents;
    vector<int> size;
    int num_components = 0;

    int find(int a) {
        if (parents[a] != a) {
            parents[a] = find(parents[a]);
        }

        return parents[a];
    }

    bool unite(int a, int b) {
        int root_a = find(a);
        int root_b = find(b);

        if (root_a == root_b) {
            return false;
        }

        if (size[root_b] > size[root_a]) {
            std::swap(root_b, root_a);
        }

        // root a eats root b
        parents[root_b] = root_a;
        size[root_a] += size[root_b];
        num_components--;

        return true;
    }

public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) return false;

        num_components = n;
        parents.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }

        for (auto &edge : edges) {
            unite(edge[0], edge[1]);
        }

        if (num_components != 1) {
            return false;
        }
        return true;
    }
};
// divergences: 
// - missed edge case: edges.size()
// - DSU - had to verify my union by size
// - TLA as was doing find(a) instead of find(parents[a]) 
