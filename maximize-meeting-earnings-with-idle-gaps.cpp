class Solution {
    vector<vector<long long>> memo;
    
    int nextValidMeeting(int i, const vector<vector<int>>& intervals) {
        int lo = i + 1;
        int hi = intervals.size();
    
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
    
            if (intervals[mid][0] < intervals[i][1]) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
    
        return lo;
    }

    long long dp(int i, int prevEnd, vector<vector<int>>& meetings) {
        if (i >= meetings.size()) return 0;
        if (memo[i][prevEnd + 1] != -1) return memo[i][prevEnd + 1];

        // skip all overlapping meetings. must binary search
        int next = nextValidMeeting(i, meetings);

        long long idle = 0;

        if (prevEnd != -1) {
            idle = meetings[i][0] - meetings[prevEnd][1];
        }
        
        long long select = meetings[i][2] + dp(next, i, meetings);
        long long skip = dp(i + 1, prevEnd, meetings);

        return memo[i][prevEnd + 1] = max(idle + select, skip);
    }
public:
    long long maxEarnings(vector<vector<int>>& meetings) {
        int n = meetings.size();
        if (n == 1) return meetings[0][2];

        memo = vector<vector<long long>>(n, vector<long long>(n + 1, -1));

        sort(meetings.begin(), meetings.end());

        return dp(0, -1, meetings);
    }
};
// divergences:
// - memoization was missing items that WERE in the state, i overlooked it. I needed to include prevEnd
// - prevEnd should represent previous index not the previous meeting time value


// convergences:
// - noted that meetings seems adequate don't need a new events vector for sweepline which seems accurate
// - O/1 knapsack interval DP
// - logic was pretty good
