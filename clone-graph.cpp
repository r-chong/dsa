/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return node;

        // og |-> clone
        unordered_map<Node*, Node*> clone;
        unordered_map<int, bool> visited;

        // contains og nodes
        queue<Node*> q;
        clone[node] = new Node(node->val);
        visited[node->val] = true;
        q.push(node);

        while (!q.empty()) {
            // curr starts as an original
            Node* curr = q.front();
            q.pop();

            for (Node* og_nei : curr->neighbors) {
                if (!clone.contains(og_nei)) {
                    clone[og_nei] = new Node(og_nei->val);
                }

                clone[curr]->neighbors.push_back(clone[og_nei]);

                if (visited[og_nei->val]) {
                    continue;
                }

                // push other originals
                q.push(og_nei);
                visited[og_nei->val] = true;
            }
        }

        return clone[node];
    }
};
// divergences:
// - started coding too early; was 60% fluent but the last 40% took like 40 mins
// - switched between using int as key and pointer as key
// - unsure what curr should look like
// - basically had to rederive iterative bfs... not good
// - went back and forth about adding size guard around for all neighbours
// - was editing curr->neighbors instead of clone[curr]->neighbors which gave heap use after free
