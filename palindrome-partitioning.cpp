class Solution {
    // TC: O(n), SC: no auxilary
    // n = size of s
    bool isPalindrome (const string &s) {
        return std::equal(
            s.begin(),
            s.begin() + s.size() / 2,
            s.rbegin()
            // s.rbegin() + s.size() / 2 <- This can be omitted
        );
    }
    // divergences:
    // - didn't know rbegin
    // - didn't understand equal syntax. So we have the start element, and how many values to compare, and then start of second, and optional how many items to compare

    void validStringsAtSizeI(int i, int n, vector<string> &current, vector<vector<string>> &res, const string& s, int len) {
        if (i == s.size()) {
            res.push_back(current);
            return;
        }

        if (i + n > s.size()) return;

        string ss = s.substr(i, n);
        
        // only push current if the substring is valid
        if (isPalindrome(ss)) {
            current.push_back(ss);
            validStringsAtSizeI(i + n, 1, current, res, s, len);
            current.pop_back();
        }

        // No cutting current substr, just extend
        validStringsAtSizeI(i, n + 1, current, res, s, len);
    }
public:
    // TC: O(n), SC: O(n)
    // n = size of s
    vector<vector<string>> partition(string s) {
        int len = s.size();
        vector<vector<string>> res;
        vector<string> current;

        validStringsAtSizeI(0, 1, current, res, s, len);

        return res;
    }
};
// divergences:
// - started size at k=0 instead of k=1
// - need n > len not n >= len that means that n cannot have n partitions
// - i + n - 1
// - had non unique values - I created a set when I shouldn't have had non unique values in the first place (meant my backtracking was overlapping)
// - did i++ instead of k++ just forgetting what the name of my iterator was
// - set initial size to 0 instead of 1
// - I had thought with the current approach I was doing, that I should backtrack when extending the current string, however I should only backtrack around valid palindromes. The reason? Because I'm working with start (i) and size (n) so I shouldn't need to add the individual WIP substring to current, only the finished copy

// - I need to try the canonical solution
// - I also need to try this using DP I think it's possible if I memoize overlapping substrings