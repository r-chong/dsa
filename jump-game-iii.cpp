class Solution {
public:
    bool search(vector<int>& arr, int i, vector<int> &memo) {
        if (i < 0 || i >= arr.size()) {
            return false;
        }

        // if in progress OR already processed and confirmed bad
        if (memo[i] == 1 || memo[i] == 2) {
            return false;
        }

        // start processing
        int v = arr[i];
        memo[i] = 1;

        if (v == 0) { 
            return true;
        }

        if (search(arr, i - v, memo) || search(arr, i + v, memo)) {
            return true;
        };
        
        // process failed, prevent future processing
        memo[i] = 2;
        return false;
    }
 
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        vector<int> memo(n, 0);
        
        return search(arr, start, memo);
    }
};

// // BROKEN 3 state dp

// class Solution {
// public:
//     bool search(vector<int>& arr, int i, vector<int> &memo) {
//         if (i < 0 || i >= arr.size()) {
//             return false;
//         }

//         // set to in progress
//         if (memo[i] == 0) {
//             memo[i] = 1;
//         }

//         // false if processed and bad
//         if (memo[i] == 2) {
//             return false;
//         }

//         int v = arr[i];

//         // true if reach end
//         if (v == 0) { 
//             // update memo necessary?
//             return true;
//         }

//         if (search(arr, i - v, memo) || search(arr, i + v, memo)) {
//             return true;
//         };
        
//         memo[i] = 2;
//         return false;
//     }
 
//     bool canReach(vector<int>& arr, int start) {
//         int n = arr.size();
//         vector<int> memo(n, 0);
        
//         return search(arr, start, memo);
//     }
// };

// // BROKEN dp attempt

// class Solution {
// public:
//     bool search(vector<int>& arr, int i, vector<int> &memo) {
//         if (i < 0 || i >= arr.size()) {
//             return false;
//         }

//         int v = arr[i];

//         if (memo[i] != -1) {
//             return memo[i];
//         }

//         if (v == 0) { 
//             return true;
//         }

//         // issue: looping when can't find
//         // what is the SIMPLEST BRUTEST SOLUTION ?
//         memo[i] = search(arr, i - v, memo) || search(arr, i + v, memo);
//         return memo[i];
//     }
 
//     bool canReach(vector<int>& arr, int start) {
//         int n = arr.size();
//         vector<int> memo(n, -1);
        
//         return search(arr, start, memo);
//     }
// };