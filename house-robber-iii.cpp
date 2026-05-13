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
    int rob(TreeNode* root) {
        auto [take, skip] = dfs(root);

        return max(take, skip);
    }

    pair<int, int> dfs(TreeNode* node) {
        // base case (below leaf nodes)
        if (!node) {
            return {0, 0};
        }

        auto [leftTake, leftSkip] = dfs(node->left);
        auto [rightTake, rightSkip] = dfs(node->right);

        int take = node->val + leftSkip + rightSkip;
        int skip = max(leftTake, leftSkip) + max(rightTake, rightSkip);

        return {take, skip};
    }
};