class Solution {
    int paths(int i, int j, string& s, string& t) {
        if (j == t.size()) return 1;
        if (i == s.size() && j < t.size()) return 0;

        int use = 0;
        int skip = paths(i + 1, j, s, t);
        if (s[i] == t[j]) {
            use = paths(i + 1, j + 1, s, t);
        }
        
        return use + skip;
    }
public:
    int numDistinct(string s, string t) {
        return paths(0, 0, s, t);
    }
};
// divergences:
// - no need for index - 1 since our base cases is actually checking for past the end not valid indices

class Solution {
    vector<vector<int>> memo;

    int paths(int i, int j, string& s, string& t) {
        if (j == t.size()) return 1;
        if (i == s.size() && j < t.size()) return 0;
        if (memo[i][j] != -1) return memo[i][j];

        int use = 0;
        int skip = paths(i + 1, j, s, t);
        if (s[i] == t[j]) {
            use = paths(i + 1, j + 1, s, t);
        }
        
        return memo[i][j] = use + skip;
    }
public:
    int numDistinct(string s, string t) {
        memo = vector<vector<int>>(s.size(), vector<int>(t.size(), -1));

        return paths(0, 0, s, t);
    }
};
// divergences:
// - no need for index - 1 since our base cases is actually checking for past the end not valid indices
// - didn't follow my own i,j indexing order