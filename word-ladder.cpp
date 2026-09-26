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
// CHATGPT:
// divergences:
// - I created buckets but then I started to traverse them. See below for different mindsets
// - incremented i in the k loop
// - had to search how to loop and print out a unordered map
// - had to look up level by level bfs
// - forgot to update visited

// NEETCODE:
// divergences:
// - Neetcode included a case where the destination word is in the wordlist already, in which case no characters have to be changed.
// - He used std::deque for his queue instead of std::queue
// - His queue contains actual words like "hit", "hot", "dot". wildcard strings are only an indexing mechanism for finding neighbors. so they are just keys in a hash map that let you quickly ask: “Which words differ from this word by exactly one character?”
// - He added the beginning word to the set of visited
// - He used level order traversal but did not do an additional loopover for each combination of begin word

// convergences:
// - Used the same idea for the * building
// - He used the init path=1, return +1 method (we count nodes not edges so must include start and end. Either offset by +2 at the end or update the init as well)

// Aadi:
// divergences:
// - He had parallel unordered_map<string, vector<string>> : "graph" and "buckets". I think buckets held the Kleene Star/wildcard patterns while graph had the real strings
// - When building the graph, he pushed the word patterns to the buckets
// - He used range-based for loop; is that advantageous for here?
// - He used one initialization of s and reset it each time
// - He used std::deque instead of std::queue
// - He simply used set instead of map for visited (any chance of duplicates?)
// - He cout'ed throughout; size of graph... 
// - He initialized time to 0

// convergences: 
// - He used level order traversal with variable named "time"