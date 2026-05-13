class Solution {
public:
    const long long MOD = 1e9 + 7;
    long long total = 0;
    long long best = 0;

    long long sum(TreeNode* root) {
        if (!root) return 0;

        return root->val + sum(root->left) + sum(root->right);
    }

    void tryEveryNode(TreeNode* root) {
        if (!root) return;

        long long subtree = sum(root);
        long long rest = total - subtree;

        best = max(best, subtree * rest);

        tryEveryNode(root->left);
        tryEveryNode(root->right);
    }

    int maxProduct(TreeNode* root) {
        total = sum(root);

        tryEveryNode(root);

        return best % MOD;
    }
};