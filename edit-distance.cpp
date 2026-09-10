class Solution {
    vector<vector<int>> memo;

    // insert a character means j progresses but i doesnt
    // delete a character means i progresses but j doesnt
    // replace a character means i progresses i progresses and j progresses

    // i representing position in curr, j representing position in target
    int dp(int i, int j, string& word1, string& word2) {
        if (j == word2.size()) return word1.size() - i;
        if (i == word1.size()) return word2.size() - j;
        if (memo[i][j] != -1) return memo[i][j];

        if (word1[i] == word2[j]) {
            return memo[i][j] = dp(i + 1, j + 1, word1, word2);
        }

        int ins = 1 + dp(i, j + 1, word1, word2);
        int del = 1 + dp(i + 1, j, word1, word2);
        int rpl = 1 + dp(i + 1, j + 1, word1, word2);

        return memo[i][j] = min({ins, del, rpl});
    }
public:
    int minDistance(string word1, string word2) {
        memo = vector<vector<int>>(word1.size(), vector<int>(word2.size(), -1));

        return dp(0, 0, word1, word2);
    }
};
// divergences:
// - got confused on should i condition on any of: insert, delete, replace
// - got confused on stopping condition for i. i should not reference word2 it only indexes word1
// - missed "chars alreday match" case
// - got confused which should be r,c: i,j or j,i. the answer is all that matters is consistency
// - trivial: memo[i][j] != -1 not == -1