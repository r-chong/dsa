// TC: O(n), SC: O(n)
// n = strlen of x
class Solution {
public:
    bool isPalindrome(int x) {
        string str1 = to_string(x);
        // copy constructor
        string str2(str1);

        reverse(str2.begin(), str2.end());

        return (str1 == str2);
    }
};
// divergences:
// - naming
// - needed to look up to_string, copy constructor