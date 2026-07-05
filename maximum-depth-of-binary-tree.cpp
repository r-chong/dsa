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
public:
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
    }
};

// divergences:
// the +1 belongs at the node you’re currently standing on, not as some special-case “return 1” somewhere.

// - made unnecessary extra function
// - when do i need a separate function for these tree problems?
// If the function can say “answer for this node = combine answers from children”, no helper.
// If the function needs to carry information downward or update an outside/global answer, use a helper.