class Solution {
public:

    string encode(vector<string>& strs) {
        if (strs.size() == 0) return "";
        string encoded = "";

        for (string s : strs) {
            int len = s.size();
            encoded += to_string(len) + "#" + s;
        }

        return encoded;
    }

    vector<string> decode(string s) {
        vector<string> decoded;
        if (s.size() == 0) return decoded;

        int i = 0;
        while (i < s.size()) {
            int sz = 0;

            // read all digits until '#'
            while (s[i] != '#') {
                sz = sz * 10 + (s[i] - '0');
                i++;
            }

            // skip '#'
            i++;

            string curr = s.substr(i, sz);
            decoded.push_back(curr);

            // skip the actual string
            i += sz;
        }

        return decoded;
    }
};
// divergences:
// - had to look up to_string()
// - forgot to subtract '0'
// - size == 0 case