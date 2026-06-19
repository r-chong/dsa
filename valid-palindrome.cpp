// TC: O(n), SC: O(1)
class Solution {
public:
    bool isPalindrome(string s) {
        // erase remove idiom
        s.erase(remove_if(s.begin(), s.end(), [](unsigned char c) {
            return !isalnum(c);
        }), s.end());

        if (s.size() == 1) return true;
        
        int n = s.size();
        int l = 0;
        int r = n - 1;

        while (l < r) {
            if (tolower(s[l]) != tolower(s[r])) {
                return false;
            }

            l++;
            r--;
        }

        return true;
    }
};
// divergences:
// - didn't know the erase-remove idiom
// - didn't read the problem correctly so missed the !alnum part and the lowercase part. READ PROBLEM EVEN IF EASY
