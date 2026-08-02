/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
    Node* create_or_get(Node* og, unordered_map<Node*, Node*> &map) {
        if (map.contains(og)) return map[og];
        if (og == nullptr) return og;

        Node* created = new Node(og->val);
        map[og] = created;
        created->next = create_or_get(og->next, map);
        created->random = create_or_get(og->random, map);
        return created;
    }
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> map;

        return create_or_get(head, map);
    }
}; 
// divergences:
// - created unnecessary og_curr
// - put map[og] after created->next, created->random which would've produced infinite loop as it never finds created
// - forgot `new` keyword