#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        // We check a letter and its neighbours for a cycle. If we have a cycle, that means that a letter has TWO orderings, thus the dictionary is invalid.
        std::unordered_set<char> visited;

        // If no cycle, then it can be ignored in the future.
        std::unordered_set<char> processed;

        // solution array
        std::string res;

        // create graph / build edges via traversing adjacency list
        // graph invariant: a letter is always earlier in the alphabet than its successors
        std::unordered_map<char, std::vector<char>> graph;

        // note the method that we create adjacency list
        // we are NOT building edges at this stage, only keys.
        for (const std::string& word : words) {
            for (char c : word) {
                if (graph.find(c) == graph.end()) { 
                    // is this good form?
                    graph[c] = std::vector<char>();
                }
            }
        }

        // Now, we build edges.
        // We subtract 1 from words.size() as we do not count the current word.
        for (int i = 0; i < words.size() - 1; i++) {
            std::string w1 = words[i];
            std::string w2 = words[i + 1];

            int len = min(w1.size(), w2.size());
            bool found_difference = false;

            for (int j = 0; j < len; j++) {
                if (w1[j] != w2[j]) {
                    graph[w1[j]].push_back(w2[j]);
                    found_difference = true;
                    break;
                }
            }

            // prefix case: one of the words is the prefix of another, the prefix goes first.
            if (!found_difference && w1.size() > w2.size()) {
                return "";
            }
        }

        // A letter at the end of the alphabet has no successors. We only add letter to solution array, if all of its successors have been added.
        // Post order DFS builds like follows: all of the letters with no successors (i.e., z) are added first, then x, then y
        for (auto const& [key, neighbours] : graph) {
            // return system seems fuzzy...
            if (processed.find(key) == processed.end()) {
                if (!dfs(graph, visited, processed, key, res)) {
                    return "";
                }
            }
        }

        std::reverse(res.begin(), res.end());
        return res;
    }

    // topo sort
    // reverse order DFS
    // track: unvisited, visited, processed. Can bundle all into one hashmap if I wish
    bool dfs(unordered_map<char, std::vector<char>> &graph, unordered_set<char>& visited, unordered_set<char> &processed, char c, string &res) {
        // visited.insert(c);
        if (visited.count(c)) {
            return false; // found cycle
        }

        if (processed.count(c)) {
            return true; // complete
        }

        visited.insert(c);

        // run toposort on all neighbours
        for (char n : graph[c]) {
            if (!dfs(graph, visited, processed, n, res)) {
                return false;
            } 
        }
        // we maintain the same visited and processed sets. What differentiates them is the fact that we erase visited after out of scope, vs. always stays in processed.
        visited.erase(c);
        processed.insert(c);

        // postorder dfs: we add the node after processing (using string addition)
        res += c;

        return true;
    }  
};

// --- TEST HARNESS ---

// Helper function to validate if a resulting alien dictionary string is actually valid
bool isValidTopologicalSort(const vector<string>& words, const string& result, const string& expected) {
    // If we expect failure/cycle, the result must be empty
    if (expected == "") return result == "";
    
    // If the expected string is not empty but we returned empty, it failed
    if (result == "") return false;

    // The result must contain the exact same unique characters as the expected answer
    if (result.length() != expected.length()) return false;

    unordered_map<char, int> position;
    for (int i = 0; i < result.length(); i++) {
        position[result[i]] = i;
    }

    // Verify all graph edges are respected in the result string
    for (size_t i = 0; i < words.size() - 1; ++i) {
        string w1 = words[i];
        string w2 = words[i + 1];
        for (size_t j = 0; j < min(w1.length(), w2.length()); ++j) {
            if (w1[j] != w2[j]) {
                // The character from w1 must appear BEFORE the character from w2
                if (position[w1[j]] > position[w2[j]]) {
                    return false;
                }
                break;
            }
        }
    }
    return true;
}

void runTest(int testNum, vector<string> words, string expected) {
    Solution sol;
    string result = sol.alienOrder(words);
    
    cout << "Test " << testNum << ": ";
    
    if (isValidTopologicalSort(words, result, expected)) {
        cout << "[PASS] Result: \"" << result << "\"\n";
    } else {
        cout << "[FAIL] -> Expected an equivalent valid sort to: \"" << expected << "\", Got: \"" << result << "\"\n";
    }
}

int main() {
    cout << "Running Alien Dictionary Tests...\n";
    cout << "---------------------------------\n";

    // Original Examples
    vector<string> words1 = {"kaa", "akcd", "akca", "cak", "cad"};
    runTest(1, words1, "kdac"); 

    vector<string> words2 = {"b", "a"};
    runTest(2, words2, "ba");

    vector<string> words3 = {"ab", "a", "b"};
    runTest(3, words3, "");

    vector<string> words4 = {"a", "b", "a"};
    runTest(4, words4, "");

    // New Examples
    vector<string> words5 = {"wrt", "wrf", "er", "ett", "rftt"};
    runTest(5, words5, "wertf"); 

    vector<string> words6 = {"z", "x"};
    runTest(6, words6, "zx");

    vector<string> words7 = {"z", "x", "z"};
    runTest(7, words7, "");

    return 0;
}