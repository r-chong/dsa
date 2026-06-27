class Solution {
public:
    // TC: O(nlogn), SC: no auxilary
    bool isAnagramSort(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());

        return s == t;
    }

    // TC: O(n), SC: O(n)
    // technically O(2n)
    bool isAnagramDoubleArray(string s, string t) {
        if (s.size() != t.size()) return false;

        vector<int> ss(26);
        vector<int> st(26);

        for (int i = 0; i < s.size(); i++) {
            char cs = s[i] - 'a';
            char ct = t[i] - 'a';

            ss[cs]++;
            st[ct]++;
        }

        return ss == st;
    }

    // TC: O(n), SC: O(n)
    bool isAnagramSingleArray(string s, string t) {
        if (s.size() != t.size()) return false;

        vector<int> eq(26);

        for (int i = 0; i < s.size(); i++) {
            char cs = s[i] - 'a';
            char ct = t[i] - 'a';

            eq[cs]++;
            eq[ct]--;
        }

        for (int e : eq) {
            if (e != 0) {
                return false;
            }
        }
        return true;
    }
};