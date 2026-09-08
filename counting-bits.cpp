// Top-down DP
// start from a larger problem n and ask for a smaller subproblem
class Solution {
    vector<int> ans;

    // we split every single n and subproblem into FIRST and REST and each f invocation only adds information about FIRST
    // f returns the number of 1's in n
    int f(int n) {
        if (ans[n] != -1) return ans[n];

        return ans[n] = f(n >> 1) + (n & 1);
    }
public:
    // TC: O(n + 1), SC: O(n), SC auxilary: O(logn)
    // We cannot have n calls on the stack because the subproblem always halves n
    vector<int> countBits(int n) {
        ans = vector<int>(n + 1, -1);
        ans[0] = 0;

        for (int i = 0; i <= n; i++) {
            f(i);
        }

        return ans;
    }
};
// I'm surprised I can discard the lvalue of f()

// Bottom-up DP
// start with known base cases, build up larger answers from already-computed smaller states
class Solution {
    vector<int> ans;
public:
    // TC: O(n + 1), SC: O(n)
    vector<int> countBits(int n) {
        ans = vector<int>(n + 1, -1);
        ans[0] = 0;

        for (int x = 0; x <= n; x++) {
            ans[x] = ans[x >> 1] + (x & 1);
        }

        return ans;
    }
};

// what is:  __builtin_popcount in C++
// This problem is really good for illustrating top-down vs bottom-up DP