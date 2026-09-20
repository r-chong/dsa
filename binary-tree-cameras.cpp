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
    int min_cameras = 0;

    enum {
        NEEDS_COVERAGE,
        IS_COVERED,
        PLACED_CAMERA
    };

    int cover(TreeNode* node) { 
        if (!node) {
            return IS_COVERED;
        }

        int left = cover(node->left);
        int right = cover(node->right);

        if (left == NEEDS_COVERAGE || right == NEEDS_COVERAGE) {
            min_cameras++;
            return PLACED_CAMERA;
        } else if (left == PLACED_CAMERA || right == PLACED_CAMERA) {
            return IS_COVERED;
        } else if (left == IS_COVERED && right == IS_COVERED) {
            return NEEDS_COVERAGE;
        }

        return -1;
    }
public:
    int minCameraCover(TreeNode* root) {
        int r = cover(root);

        if (r == NEEDS_COVERAGE) {
            min_cameras++;
        }

        return min_cameras;
    }
};
// divergences:
// - kept thinking this is take/skip 0/1 knapsack DP. it's not even DP
// - this is a greedy approach so don't classify too early
// - needed hint for keeping states. Bottom-up means you use the return value instead of a propagated input
// - enum needs ; at the end

// convergences:
// - I failed case with [0], so I just checked the root's return value and returned 1. this solved one additional test case
// - then I failed case where I was off-by-one. So I instead just updated min_cameras and it worked first try!!
