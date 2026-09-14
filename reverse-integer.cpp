// TC: either O(1) as input is always 1: x, OR we use length of x

// Both interpretations are valid, depending on how you define input size.

// If x is a fixed-width 32-bit integer, then there are at most 10 decimal digits, so technically time is O(1).
// If define input size as the number of digits, d, then it is O(d), equivalently O(log |x|). The log is log base ten so we're just dividing by how many times we remove a 10's place.

// For LeetCode-style analysis, I’d usually write:

// TC: O(log |x|)
// SC: O(1)

// Int overflow guard solution
class Solution {
public:
    int reverse(int x) {
        int reversed = 0;

        // repeatedly insert rightmost side
        while (x != 0) {
            int digit = x % 10;
            if (reversed > INT_MAX / 10 || reversed < INT_MIN / 10) {
                return 0;
            }
            reversed = reversed * 10 + digit;
            x /= 10;
        }

        return reversed;
    }
};

// Long long with final check solution
class Solution {
public:
    int reverse(int x) {
        // append to new number (long long) since we can have leading zeros become trailing 0s
        long long reversed = 0;

        // repeatedly insert rightmost side
        while (x != 0) {
            int digit = x % 10;
            reversed = reversed * 10 + digit;
            x /= 10;
        }

        if (reversed < INT_MIN || reversed > INT_MAX) return 0;

        return reversed;
    }
};