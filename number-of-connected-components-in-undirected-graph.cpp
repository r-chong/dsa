// TC: O(n + m), SC: O(n) 
// technically TC is O(n + m * α(n))
// m = edges.size()
class Solution {
private:
    vector<int> parents;
    vector<int> size;g
    int count;
public:
    int find(int a) {
        if (parents[a] != a) {
            return find(parents[a]);
        }

        return a;
    }

    void unite(int a, int b) {
        int root_a = find(a);
        int root_b = find(b);

        if (root_a == root_b) {
            return;
        }

        // if not equal put in the larger one
        if (size[root_b] > size[root_a]) {
            swap(root_a, root_b);
        }

        parents[root_b] = root_a;
        size[root_a] += size[root_b];
        count--;
    }

    int countComponents(int n, vector<vector<int>>& edges) {
        parents.resize(n);
        size.resize(n, 1);
        this->count = n;

        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }

        for (auto &edge : edges) {
            int a = edge[0];
            int b = edge[1];

            unite(a, b);
        }

        return count;
    }
};

// divergences:
// - my "brute force" was actually just counting edges which can be done with edges.size();
// - you don't need this-> unless local name shadows the class variable name
// - resize not reserve (reserve allocates but size() is still 0)
// - implementing DSU
//      - took too long to create unite()
//      - work with roots never originals
//      - union by size done wrong, must access size array obviously
//      - subtract total count not add
//      - forgot to path compress (it's a one line change)