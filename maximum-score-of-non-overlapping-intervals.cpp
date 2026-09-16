class Solution {
    vector<vector<pair<long long, vector<int>>>> memo;
    vector<vector<bool>> seen;
public:
    pair<long long, vector<int>> dp(
        int i,
        int remaining,
        vector<vector<int>>& events
    ) {
        if (remaining == 0 || i >= events.size()) {
            return {0, {}};
        }

        if (seen[i][remaining]) {
            return memo[i][remaining];
        }

        // bisect to find FIRST okay K. after that, since we are sorted, we can just check further ones
        int lo = i + 1;
        int hi = events.size();

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (events[mid][0] > events[i][1]) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        int k = lo;

        auto take = dp(k, remaining - 1, events);
        take.first += events[i][2];
        take.second.push_back(events[i][3]);
        sort(take.second.begin(), take.second.end());

        auto skip = dp(i + 1, remaining, events);

        pair<long long, vector<int>> ans;

        // hierarchy: compare score, if neq then compare lexographic
        if (take.first > skip.first) {
            ans = take;
        } else if (skip.first > take.first) {
            ans = skip;
        } else {
            ans = (take.second < skip.second) ? take : skip;
        }

        seen[i][remaining] = true;
        return memo[i][remaining] = ans;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        // {left, right, weight}
        vector<vector<int>> events;

        for (int i = 0; i < intervals.size(); i++) {
            events.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        sort(events.begin(), events.end());

        memo.resize(
            events.size(),
            vector<pair<long long, vector<int>>>(5)
        );

        seen.resize(
            events.size(),
            vector<bool>(5, false)
        );

        return dp(0, 4, events).second;
    }
};
// this is the most cancerous problem I've ever seen