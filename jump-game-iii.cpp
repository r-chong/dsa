class Solution {
public:
    bool search(vector<int>& arr, int i, vector<int> &dp) {
        if (i < 0 || i >= arr.size()) {
            return false;
        }

        // if in progress OR already processed and confirmed bad
        if (dp[i] == 1 || dp[i] == 2) {
            return false;
        }

        // start processing
        int v = arr[i];
        dp[i] = 1;

        if (v == 0) { 
            return true;
        }

        if (search(arr, i - v, dp) || search(arr, i + v, dp)) {
            return true;
        };
        
        // process failed, prevent future processing
        dp[i] = 2;
        return false;
    }
 
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        vector<int> dp(n, 0);
        
        return search(arr, start, dp);
    }
};

// // BROKEN 3 state dp

// class Solution {
// public:
//     bool search(vector<int>& arr, int i, vector<int> &dp) {
//         if (i < 0 || i >= arr.size()) {
//             return false;
//         }

//         // set to in progress
//         if (dp[i] == 0) {
//             dp[i] = 1;
//         }

//         // false if processed and bad
//         if (dp[i] == 2) {
//             return false;
//         }

//         int v = arr[i];

//         // true if reach end
//         if (v == 0) { 
//             // update dp necessary?
//             return true;
//         }

//         if (search(arr, i - v, dp) || search(arr, i + v, dp)) {
//             return true;
//         };
        
//         dp[i] = 2;
//         return false;
//     }
 
//     bool canReach(vector<int>& arr, int start) {
//         int n = arr.size();
//         vector<int> dp(n, 0);
        
//         return search(arr, start, dp);
//     }
// };

// // BROKEN dp attempt

// class Solution {
// public:
//     bool search(vector<int>& arr, int i, vector<int> &dp) {
//         if (i < 0 || i >= arr.size()) {
//             return false;
//         }

//         int v = arr[i];

//         if (dp[i] != -1) {
//             return dp[i];
//         }

//         if (v == 0) { 
//             return true;
//         }

//         // issue: looping when can't find
//         // what is the SIMPLEST BRUTEST SOLUTION ?
//         dp[i] = search(arr, i - v, dp) || search(arr, i + v, dp);
//         return dp[i];
//     }
 
//     bool canReach(vector<int>& arr, int start) {
//         int n = arr.size();
//         vector<int> dp(n, -1);
        
//         return search(arr, start, dp);
//     }
// };