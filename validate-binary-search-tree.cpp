/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    bool checker(TreeNode* node, long long min, long long max) {
        if (node == nullptr) return true;
        
        bool meetsConditions = (node->val < max) && (node->val > min);

        // check left child's value vs max && run checker on left child
        bool left = checker(node->left, min, node->val);

        // check right child's value vs min && run checker on right child
        bool right = checker(node->right, node->val, max);

        return meetsConditions && left && right;
    }
public:
    // loosest bounds from true root
    // left: starting max is root's value, starting min INT_MIN
    // right: starting min is root's value, starting max INT_MAX
    bool isValidBST(TreeNode* root) {
        bool left = checker(root->left, LLONG_MIN, root->val);
        bool right = checker(root->right, root->val, LLONG_MAX);
        
        return left && right;
    }
};
// divergences:
// - didn't originally create separate function with additional information
// - thought i had to pass root through
// - didn't have long long (/ LLONG_MIN/LLONG_MAX) so a case where INT_MIN was the root and INT_MAX was a child had overflow