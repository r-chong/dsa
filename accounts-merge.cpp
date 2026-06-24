// TC: O(E * α(n) + UlogU), SC: O(n + U)
// inverse ackerman

// n = number of accounts
// E = total number of email entries across all accounts
// U = number of unique emails
class Solution {
private:
    vector<int> parents;
    vector<int> size;
    int num_unique;

    int find(int a) {
        if (parents[a] != a) {
            parents[a] = find(parents[a]);
        }

        return parents[a];
    }

    bool unite(int a, int b) {
        int root_a = find(a);
        int root_b = find(b);

        if (root_a == root_b) {
            return false;
        }

        if (size[root_b] > size[root_a]) {
            std::swap(root_a, root_b);
        }

        parents[root_b] = root_a;
        size[root_a] += size[root_b];
        num_unique--;

        return true;
    }
public: 
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        parents.resize(n);
        size.resize(n, 1);
        num_unique = n;

        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }

        unordered_map<string, int> emails;

        // email : group. i represents row. j represents email
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                // if we have seen this email before in emails[email]
                // add it to existing group
                std::string email = accounts[i][j];

                if (emails.count(email)) {
                    unite(emails[email], i);
                } else {
                    emails[email] = i;
                }
            }
        }

        // group : all associated emails
        unordered_map<int, vector<string>> grouped;
        for (auto& [email, index] : emails) {
            int group = find(index);
            
            grouped[group].push_back(email);
        }

        // sort each group's emails
        vector<vector<string>> res;
        for (auto& [group, emails] : grouped) {
            // add name to result
            vector<string> g;

            g.push_back(accounts[group][0]);

            // now add all emails in order
            sort(emails.begin(), emails.end());

            for (string& email : emails) {
                g.push_back(email);
            }

            res.push_back(g);
        }

        return res;
    }
};
// divergences:
// - didn't think I should do multiple for loops at depth 1 but it's ok
// - got confused with data passthrough
// - use unordered map sometimes
// - append don't set index directly
// - was afraid to use sort()