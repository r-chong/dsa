class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        if (target == "0000") return 0;

        queue<string> q;
        unordered_set<string> dead(deadends.begin(), deadends.end());
        if (dead.contains("0000")) return -1;

        unordered_set<string> visited;
        visited.insert("0000");
        q.push("0000");

        int minTurns = 0;

        while (!q.empty()) {
            int levelSize = q.size();

            for (int k = 0; k < levelSize; k++) {
                string curr = q.front();
                q.pop();

                if (curr == target) {
                    return minTurns;
                }

                // for all positions
                for (int i = 0; i < 4; i++) {
                    string next = curr;

                    // try both directions
                    next[i] = (curr[i] - '0' + 1) % 10 + '0';

                    if (!dead.contains(next) && !visited.contains(next)) {
                        q.push(next);
                        visited.insert(next);
                    }

                    next = curr;
                    next[i] = (curr[i] - '0' + 9) % 10 + '0';
                    
                    if (!dead.contains(next) && !visited.contains(next)) {
                        q.push(next);
                        visited.insert(next);
                    }
                }
            }

            minTurns++;
        }
        
        return -1;
    }
};
// divergences:
// - did not see bfs here
// - initialized with 1
// - didnt consider deadends with visited
// - yeah i forgot deadends entirely