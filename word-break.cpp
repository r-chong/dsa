class Solution {
    unordered_map<int, int> memo;

    bool dfs(int i, string& s, vector<string>& wordDict) {
        if (i == s.size()) return true;
        if (memo.contains(i)) return memo[i];

        // try all words, combine in OR
        bool foundValid = false;
        for (int k = 0; k < wordDict.size(); k++) {
            int size = wordDict[k].size();

            if (i + size > s.size()) continue;

            bool isMatch = s.substr(i, size) == wordDict[k];

            foundValid |= (isMatch && dfs(i + size, s, wordDict));
        }
        // if no words are valid at i, then we cannot possibly hit eos, so false

        return memo[i] = foundValid;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        memo = unordered_map<int, int>();

        return dfs(0, s, wordDict);
    }
};