class Solution {
public:
    int check(string &s, int i, vector<int> &seen) {
        // goal of this function, start at an index, choose decision, and take it all the way
        int num_possible = 0;
        int n = s.size();

        // base cases
        if (i > n - 1) {
            // if it was invalid, then we would have ended already. So, we return
            return 1;
        }

        if (s[i] == '0') {
            // invalid
            return 0;
        }
q
        // if at the end, AND not 0, then end the path
        if (i == n - 1) {
            return check(s, i + 1, seen);
        }

        if (seen[i] != -1) {
            return seen[i];
        }

        // if 1, then teens valid
        if (s[i] == '1') {
            seen[i] = check(s, i + 1, seen) + check(s, i + 2, seen);
            return seen[i];
        }

        // if 2, then 20,21,22,23,24,25,26 valid
        if (s[i] == '2') {
            if (s[i + 1] - '0' <= 6) {
                seen[i] = check(s, i + 1, seen) + check(s, i + 2, seen);
                return seen[i];
            }

            seen[i] = check(s, i + 1, seen);
            return seen[i];
        }

        seen[i] = check(s, i + 1, seen);
        return seen[i];
    }

    int numDecodings(string s) {
        vector<int> seen(s.size() + 1, -1);

        return check(s, 0, seen);
    }
};