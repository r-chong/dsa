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
    // BRUTE FORCE PROBLEM:
    // product between every node's sum, and all else
    // given any node you can cut above it and compare against the total - that node

    // we need to accumulate in order to save whats above the dfs
    long long total = 0;
    long long best = 0;
    const int MOD = 1e9 + 7;

    // sum is just a helper not the main dfs
    long long sum(TreeNode* root) {
        if (!root) {
            return 0;
        }

        return root->val + sum(root->left) + sum(root->right);
    }

    // save total once here
    // this is the only spot we can do it
    // then run dfs to treat other nodes
    // the only other job of this function is to return best
    long long maxProduct(TreeNode* root) {
        total = sum(root);
        dfs(root);

        return best % MOD;
    }

    // the main dfs serves to treat every node as the root
    // so run (subtree * (total - subtree) for each node
    // compare against global best
    long long dfs(TreeNode* root) {
        if (!root) {
            return 0;
        }

        long long left = dfs(root->left);
        long long right = dfs(root->right);

        long long subtree = root->val + left + right;

        best = max(best, subtree * (total - subtree));

        return subtree;
    }
};