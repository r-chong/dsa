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
        if (connected(a, b)) {
            return false;
        }

        int find_a = find(a);
        int find_b = find(b);

        // Merge to larger size. We update the root, not a or b.
        // We don't care about updating the size index of the smaller component
        // as that index is no longer a root.
        if (this->size[find_a] >= this->size[find_b]) {
            this->parents[find_b] = find_a;

            this->size[find_a] += this->size[find_b];
        } else {
            this->parents[find_a] = find_b;

            this->size[find_b] += this->size[find_a];
        }

        this->num_components--;

        return true;
    }

    // Given nodes 'a' and 'b' return if they are in the same connected component.
    bool connected(int a, int b) {
        int find_a = find(a);
        int find_b = find(b);

        return find_a == find_b;
    }

    // return total number of connected components.
    int count() {
        return this->num_components;
    }
};
