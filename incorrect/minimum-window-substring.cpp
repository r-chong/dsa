// brute force, assisted :')
// right grows to gain missing characters
// left shrinks to remove unnecessary characters
class Solution {
public:
    int getIndex(char c) {
        if ('A' <= c && c <= 'Z') {
            return c - 'A';
        } else {
            return 26 + (c - 'a');
        }
    }

    bool covers(array<int, 52>& has, array<int, 52>& needs) {
        for (int i = 0; i < 52; i++) {
            if (has[i] < needs[i]) {
                return false;
            }
        }

        return true;
    }

    string minWindow(string s, string t) {
        int n = s.size();

        array<int, 52> freq_t{};

        // populate freq_t
        for (char c : t) {
            freq_t[getIndex(c)]++;
        }

        string best = "";

        for (int l = 0; l < n; l++) {
            array<int, 52> freq_s{};

            for (int r = l; r < n; r++) {
                char c = s[r];

                freq_s[getIndex(c)]++;

                if (covers(freq_s, freq_t)) {
                    // r - l + 1 is the size of the window, starting at left
                    string candidate = s.substr(l, r - l + 1);

                    if (best == "" || candidate.size() < best.size()) {
                        best = candidate;
                    }

                    break;
                }
            }
        }        

        return best;
    }
};
// divergences:
// - array takes 2 args