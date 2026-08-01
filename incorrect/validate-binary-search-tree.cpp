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
// Brute force solution O(n^2)
class Solution {
    bool containsGEQ(TreeNode* node, TreeNode* root) {
        if (node == nullptr) {
            return false;
        }

        if (node->val >= root->val) return true;

        return containsGEQ(node->left, root) || containsGEQ(node->right, root);
    }

    bool containsLEQ(TreeNode* node, TreeNode* root) {
        if (node == nullptr) {
            return false;
        }

        if (node->val <= root->val) return true;

        return containsLEQ(node->left, root) || containsLEQ(node->right, root);
    }
public:
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        bool validImmediate = false;

        if (root->left && root->right) {
            validImmediate = root->left->val < root->val && root->right->val > root->val;
        } else if (root->left) {
            validImmediate = root->left->val < root->val;
        } else if (root->right) {
            validImmediate = root->right->val > root->val;
        } else {
            // both null
            validImmediate = true;
        }

        bool containsInvalid = containsGEQ(root->left, root) || containsLEQ(root->right, root);

        bool left = isValidBST(root->left);
        bool right = isValidBST(root->right);

        return left && right && validImmediate && !containsInvalid;
    }
};
// divergences:
// - missed the containsInvalid case