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
    int count = 0;

    void dfs(TreeNode* x, int pathMax, TreeNode* root) {
        if (x == nullptr) {
            return;
        }

        if (x->val >= pathMax) {
            count++;
            pathMax = x->val;
        }

        dfs(x->left, pathMax, root);
        dfs(x->right, pathMax, root);
    }
public:
    // TC: O(n), SC: O(h)
    // n = number of nodes in tree
    // h = height of tree
    int goodNodes(TreeNode* root) {
        dfs(root->left, root->val, root);
        dfs(root->right, root->val, root);

        return count + 1;
    }
};