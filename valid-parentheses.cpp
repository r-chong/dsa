class Solution {
    unordered_map<char, char> dict = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
public:
    bool isValid(string s) {
        stack<char> stck;

        for (char c : s) {
            if (!stck.empty() && stck.top() == dict[c]) {
                stck.pop();
                continue;
            }
            stck.push(c);
        }

        return stck.empty();
    }
};
// divergences:
// - forgot stack <type>

// convergences:
// - required little thought to implement it