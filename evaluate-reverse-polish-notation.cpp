class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        vector<string> stck;
        int ans = 0;

        for (int i = 0; i < tokens.size(); i++) {
            string c = tokens[i];
            
            if (c == "+") {
                string str_b = stck.back();
                stck.pop_back();
                string str_a = stck.back();
                stck.pop_back();
                int a = stoi(str_a);
                int b = stoi(str_b);
                stck.push_back(to_string(a + b));
            } else if (c == "-") {
                string str_b = stck.back();
                stck.pop_back();
                string str_a = stck.back();
                stck.pop_back();
                int a = stoi(str_a);
                int b = stoi(str_b);
                stck.push_back(to_string(a - b));
            } else if (c == "*") {
                string str_b = stck.back();
                stck.pop_back();
                string str_a = stck.back();
                stck.pop_back();
                int a = stoi(str_a);
                int b = stoi(str_b);
                stck.push_back(to_string(a * b));
            } else if (c == "/") {
                string str_b = stck.back();
                stck.pop_back();
                string str_a = stck.back();
                stck.pop_back();
                int a = stoi(str_a);
                int b = stoi(str_b);
                stck.push_back(to_string(a / b));
            } else {
                stck.push_back(tokens[i]);
            }
        }

        return stoi(stck.back());
    }
};
// divergences:
// - back() returns, pop_back() does not return
// - stoi doesn't work on char obviously
// - syntax; tried a while loop solution. ensure that use while(!stck.empty()) not while(stack)
