class Solution {
public:
    vector<vector<string>> findLadders(
        string beginWord,
        string endWord,
        vector<string>& wordList
    ) {
        unordered_set<string> words(wordList.begin(), wordList.end());

        // beginWord does not need to be in wordList
        if (!words.contains(endWord)) {
            return {};
        }

        unordered_map<string, vector<string>> buckets;
        vector<vector<string>> res;

        words.insert(beginWord);

        for (const string& word : wordList) {
            for (int i = 0; i < word.size(); i++) {
                string pattern = word;
                pattern[i] = '*';

                buckets[pattern].push_back(word);
            }
        }

        queue<string> q;
        unordered_set<string> visited;
        q.push(beginWord);
        visited.insert(beginWord);

        // once endWord is found, finish the current BFS level to collect all shortest parents, then stop. Due to BFS invariants the found level is the shortest level
        bool found = false;

        // we create a NEW graph to keep track of the traversal sequence
        unordered_map<string, vector<string>> parents;

        while (!q.empty() && !found) {
            int levelSize = q.size();

            // words discovered on this BFS level
            unordered_set<string> levelVisited;

            for (int k = 0; k < levelSize; k++) {
                string curr = q.front();
                q.pop();

                // generate wildcard patterns for curr
                for (int i = 0; i < curr.size(); i++) {
                    string pattern = curr;
                    pattern[i] = '*';

                    // all words in this bucket differ by one character
                    for (const string& nei : buckets[pattern]) {
                        if (visited.contains(nei)) {
                            continue;
                        }

                        // curr is a shortest-path parent of nei
                        parents[nei].push_back(curr);

                        // only enqueue nei once on this BFS level
                        if (!levelVisited.contains(nei)) {
                            q.push(nei);
                            levelVisited.insert(nei);
                        }

                        if (nei == endWord) {
                            found = true;
                        }
                    }
                }
            }

            // only after the full level finishes do these become globally visited
            for (const string& word : levelVisited) {
                visited.insert(word);
            }
        }

        if (!found) {
            return {};
        }

        vector<string> path = {endWord};

        function<void(string)> backtrack = [&](string curr) {
            if (curr == beginWord) {
                vector<string> seq = path;
                reverse(seq.begin(), seq.end());
                res.push_back(seq);
                return;
            }

            for (const string& parent : parents[curr]) {
                path.push_back(parent);
                backtrack(parent);
                path.pop_back();
            }
        };

        backtrack(endWord);

        return res;
    }
};
// convergences:
// - built the pattern adjacency list correctly

// divergences:
// - forgot pop
// - for deque didnt remember pop front
// - for deque i pushed the front but also popped the front making it like a stack not a queue