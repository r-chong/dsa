#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class DSU {
    std::vector<int> parents;
    std::vector<int> size;
    int num_components;
        
    public:

    DSU(int n) {
        parents.resize(n);
        size.resize(n);
        num_components = n;

        for (int i = 0; i < parents.size(); i++) {
            parents[i] = i;
        }

        std::fill(size.begin(), size.end(), 1);
    }

    // Given a node 'a', find the root of the associated connected component.
    // Note that parents[a] is the next node upwards, not the final root.
    // We know a node is the final root if: it is equal to its parent.
    int find(int a) {
        // path compression
        if (parents[a] != a) {
            parents[a] = find(parents[a]);
        }

        return parents[a];
    }

    // Merge the roots of two nodes 'a' and 'b'.
    // Note: union is a restricted keyword in C++
    bool unite(int a, int b) {
        int root_a = find(a);
        int root_b = find(b);

        if (root_a == root_b) return false;

        // union by size
        if (size[root_a] < size[root_b]) {
            std::swap(root_a, root_b);
        } 

        parents[root_b] = root_a;
        size[root_a] += size[root_b];

        num_components--;

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
        return num_components;
    }
};
