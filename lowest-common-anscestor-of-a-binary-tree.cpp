/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool hasDescendant(TreeNode* node, TreeNode* target) {
        if (node == nullptr) return false;
        if (node == target) return true;

        return hasDescendant(node->left, target) || hasDescendant(node->right, target);
    }

    // TC: O(n^2), SC: O(h)
    // n is number of nodes, h is height of tree
    TreeNode* lowestCommonAncestorV1(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (hasDescendant(root->left, p) && hasDescendant(root->left, q)) {
            return lowestCommonAncestor(root->left, p, q);
        } else if (hasDescendant(root->right, p) && hasDescendant(root->right, q)) {
            return lowestCommonAncestor(root->right, p, q);
        }

        return root;
    }

    // TC: O(n), SC: O(h)
    // n is number of nodes, h is height of tree
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // nullptr is a miss
        // p,q is a match
        if (root == nullptr || root == p || root == q) {
            return root;
        }

        // it's postorder traversal(stuff after recursing) so we keep going left and right. If it's not a match/is a miss, we don't return anything.
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        // At the first point we found NON-NULL returning on the left, and NON-NULL returning on right, then we're at its fork and therefore the LCA.
        if (left && right) {
            return root;
        }

        // Case for us not hitting the end yet not hitting a target either
        // That means it's only on one side.
        if (left) {
            return left;
        } else {
            return right;
        }
    }
};