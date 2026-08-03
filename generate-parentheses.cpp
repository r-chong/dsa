class Solution {
    void backtrack(int open, int unresolved, string &current, vector<string> &res, int n) {
        if (unresolved == 0 && current.size() == 2 * n) {
            res.push_back(current);
            return;
        }

        if (open < n) {
            current.append("(");
            backtrack(open + 1, unresolved + 1, current, res, n);
            current.pop_back();
        }

        if (unresolved > 0) {
            current.append(")");
            backtrack(open, unresolved - 1, current, res, n);
            current.pop_back();
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string current;

        backtrack(0, 0, current, res, n);

        return res;
    }
};
// divergences:
// - had to check if I should pass string by reference
// - conclusion was: I shouldn't need to backtrack if I pass by value
// - but I can also pass by reference for backtracking. I'll choose the latter because cannot bind to a temporary of type 'basic_string<...>'
// - had to look up string append/+ method
// - messed up find and replace (L aura) and forgot return res