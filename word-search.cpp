class Solution {
    const vector<int> DR{-1, 1, 0, 0};
    const vector<int> DC{0, 0, 1, -1};
    bool existsWord = false;

    void backtrack(int idx, int i, int j, string &current, set<pair<int, int>> &visited, vector<vector<char>> &board, const string &word) {
        int m = board.size();
        int n = board[0].size();

        if (existsWord) return;
        if (current == word) {
            existsWord = true;
            return;
        }
        if (idx >= word.size()) return;

        for (int k = 0; k < 4; k++) {
            int r = i + DR[k];
            int c = j + DC[k];

            if (r >= m || r < 0 || c >= n || c < 0) continue;
            if (board[r][c] != word[idx + 1]) continue;
            if (visited.contains({r, c})) continue;

            pair<int, int> coords = {r, c};

            current.push_back(board[r][c]);
            visited.insert(coords);
            backtrack(idx + 1, r, c, current, visited, board, word);
            current.pop_back();
            visited.erase(coords);
        }
    }
public:
    // TC: O(mn * 3^L), SC: O(L)
    // m = # rows
    // n = # cols
    // 3 is # directions we choose from each turn
    // L = word length. unique, current hold at most L entries
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        set<char> unique;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                unique.insert(board[i][j]);
            }
        }

        for (char x : word) {
            if (!unique.contains(x)) return false;
        }

        string current;
        set<pair<int, int>> visited;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (existsWord) break;
                current.push_back(board[i][j]); 
                visited.insert({i, j});
                backtrack(0, i, j, current, visited, board, word);
                current = "";
                visited.clear();
            }
        }

        return existsWord;
    }
};
// divergences:
// - didn't know if you can put pair<int,int> as key in unordered_map. The answer is, yes in C++20 and before that you must use your own hashing function. Must try it out
// - string push back for append here. couldn't use append
// - used set clear instead of erase
// - missed a & in reference of visited
// - didn't invalidate grid out of bounds
// - reused variable i for direction. change to k
// - SMH was comparing if (visited.contains({i, j})) not r,c
// - TLE'd because was searching for chars which did not appear. Therefore add a check if any chars are not present