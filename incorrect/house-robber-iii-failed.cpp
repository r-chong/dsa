 // create level sum, so we can use that array in DP
        vector<int> ls;
        int h = height(root);

        // dfs block
        queue<TreeNode*> q;

        q.push(root);

            // do a search over the tree at the start

            // for each level, add sum

            // create queue adding root
            // create array storing level sum

            // level sum[0] = root.val

            // for each level

            // add neighbours to queue, then sum

            // that gets set to level sum[i]

        // dp block

            // create dp array

            // and then calculate take or skip for each

        // return dp[i - 1]
    }

    int height(TreeNode* root) {
        // going past leaf node, then value bubbles up
        if (!root) {
            return 0;
        }

        int best = 0;
        for (Node* child : root->children) {
            best = max(height(root.left), height(root.right));
        }

        return 1 + best;
    }