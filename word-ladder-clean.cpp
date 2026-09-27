// TC: O(V + E), SC: O(V)
// We process each node (V) once. We also check each edge E
// We can have V nodes in the queue.

// Since we have wildcard strings that may not necessarily create a word (but still are work), it is technically
// TC: O(N * L^2), SC: O(N * L)

// N = number of words
// L = maximum word length (they are all the same in this problem)
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(), wordList.end());

        if (!words.contains(endWord)) {
            return 0;
        }

        unordered_map<string, vector<string>> buckets;

        words.insert(beginWord);

        // for every word we create a pattern from each. Use the pattern to update the key in graph, but value is the WORD
        for (const string& word : words) {
            for (int i = 0; i < word.size(); i++) {
                string pattern = word;
                pattern[i] = '*';

                buckets[pattern].push_back(word);
            }
        }

        queue<string> q;
        unordered_set<string> visited;

        q.push(beginWord);
        // visit on check neighbours not when it becomes current
        visited.insert(beginWord);
        int shortestPathLen = INT_MAX;
        int pathLen = 1;

        // level order bfs iterative
        while (!q.empty()) {
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++) {
                string curr = q.front();
                q.pop();

                if (curr == endWord) {
                    return pathLen;
                }

                // check all neighbours
                // as in, all patterns this word can create
                for (int j = 0; j < curr.size(); j++) {
                    string pattern = curr;
                    pattern[j] = '*';

                    // check actual words that the pattern can create
                    for (const string& next : buckets[pattern]) {
                        if (!visited.contains(next)) {
                            visited.insert(next);
                            q.push(next);
                        }
                    }

                    // MEMORY OPTIMIZATION: we have already processed this bucket from one breadth first scan. If another BFS invocation were to check it, we would find they are all visited. So might as well delete it now. This only works as we tried all values in bucket (wouldn't work for dfs).
                    buckets[pattern].clear();
                }
            }
            
            pathLen++;
        }

        return 0;
    }
};
// divergences:
// - never considered const reference
// - forgot the case where curr is endWord
// - used unordered set as a map with set[x] = true (WRONG)

// convergences:
// - remembered to update visited on neighbour check not when it becomes current