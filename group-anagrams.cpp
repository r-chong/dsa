// TC: O(n * k), SC: O(n * k)
// k = max string length
class Solution {
    public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();

        vector<vector<string>> result = {};
        unordered_map<string, vector<string>>groups;

        for (int i = 0; i < n; i++) {
            vector<int> freq(26, 0);

            for (char c : strs[i]) {
                freq[c - 'a']++;
            }
            
            string key;
            for (int x : freq) {
                key += to_string(x);
                key += '#';
            }

            groups[key].push_back(strs[i]);
        }

        for (auto& group : groups) {
            result.push_back(group.second);
        }

        return result;
    }
};
// divergences:
// - didn't know how to hash - and when I looked it up, assumed that hashes are always long long. it can be a string. depends on the case.

// - For chars, use c - 'a' to convert 'a'..'z' into 0..25.
//   This gives a compact fixed-size frequency array

// - For fixed alphabets, prefer vector<int>(26) over unordered_map<char, int>.
//   It is simpler, faster, and avoids hashing overhead.

// - The '#' delimiter prevents ambiguous keys.
//   Example: [1, 11] vs [11, 1] should not both become "111".

// Suboptimal but short solution
class Solution {
public:
    // TC: O(n*k*logk + n*k*logn), SC: O(nk)
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<multiset<char>, vector<string>> groups;

        for (string s : strs) {
            multiset<char> word(s.begin(), s.end());
            groups[word].push_back(s);
        }

        vector<vector<string>> res;

        for (auto& [key, group] : groups) {
            res.push_back(group);
        }

        return res;
    }
};
// divergences:
// - used unordered set instead of a map, forgot that we need key:value pair
// - did if(groups.contains(s)) but I can just directly do groups[word].push_back(s);
// - used unordered_map instead of map. unordered_map needs to hash its key type, and C++ does not provide a built-in std::hash<std::multiset<char>>. but map just compares keys
