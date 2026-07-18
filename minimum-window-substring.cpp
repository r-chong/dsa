// brute force, assisted :')
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

// optimal, but assisted :')
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

        int l = 0;
        array<int, 52> freq_s{};

        for (int r = l; r < n; r++) {
            char c = s[r];

            freq_s[getIndex(c)]++;

            while (covers(freq_s, freq_t)) {
                // r - l + 1 is the size of the window, starting at left
                int len = r - l + 1;

                if (best == "" || len < best.size()) {
                    best = s.substr(l, len);
                }

                freq_s[getIndex(s[l])]--;
                l++;
            }
        }

        return best;
    }
};
// divergences:
// - array takes 2 args
// - substr function (start, length)

// solution from chatgpt:
// I am including it now as I've internalized it more now.
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> need(128, 0);
        
        for (char c : t) {
            need[c]++;
        }

        int missing = t.size();
        int l = 0;
        int bestStart = 0;
        int bestLen = INT_MAX;

        for (int r = 0; r < s.size(); r++) {
            char front = s[r];
            if (need[front] > 0) {
                missing--;
            }
            // relative
            need[front]--;

            while (missing == 0) {
                int len = r - l + 1;

                if (len < bestLen) {
                    bestLen = len;
                    bestStart = l;
                }

                char back = s[l];
                need[back]++;

                if (need[back] > 0) {
                    missing++;
                }
                
                l++;
            }
        }

        if (bestLen == INT_MAX) return "";
        return s.substr(bestStart, bestLen);
    }
};