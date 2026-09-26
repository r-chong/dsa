class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size();
        unordered_map<string, vector<string>> graph(n);

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < wordList[i].size(); k++) {
                string s = wordList[i];
                s[k] = '*';

                graph[s].push_back(wordList[i]);
            }
        }

        for (const auto& [key, values] : graph) {
            cout << key << ": ";

            for (const string& value : values) {
                cout << value << " ";
            }

            cout << '\n';
        }

        int shortestPathLen = INT_MAX;

        // BFS
        int pathLen;
        queue<string> q;
        unordered_map<string, bool> visited;

        // must do this for all versions of beginWord
        for (int k = 0; k < beginWord.size(); k++) {
            pathLen = 1;
            string s = beginWord;
            s[k] = '*';
            
            q.push(s);

            while (!q.empty()) {
                int levelSize = q.size();

                for (int i = 0; i < levelSize; i++) {
                    string curr = q.front();
                    q.pop();
                    
                    // cycle
                    if (visited.contains(curr)) {
                        continue;
                    };
                    visited[curr] = true;

                    for (int j = 0; j < graph[curr].size(); j++) {
                        if (graph[curr][j] == endWord) {
                            shortestPathLen = min(pathLen, shortestPathLen);
                        }

                        for (int k = 0; k < graph[curr][j].size(); k++) {
                            string s = graph[curr][j];
                            s[k] = '*';
                            q.push(s);
                        }
                    }
                }

                pathLen++;
            }
            visited.clear();
        }

        if (shortestPathLen == INT_MAX) {
            return 0;
        }

        return shortestPathLen + 1;
    }
};
// divergences:
// - incremented i in the k loop
// - had to search how to loop and print out a unordered map
// - had to look up level by level bfs
// - forgot to update visited