class Solution {
public:
    // TC: O(nlogn), SC: O(n)
    // n = number of intervals
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // metadata: [position, type]
        // end is 1 and start is 0
        vector<vector<int>> events;
        vector<vector<int>> res;

        // JOIN [x, 0], [x, 1] where x is an index where we end and start different intervals
        for (int i = 0; i < n; i++) {
            events.push_back({intervals[i][0], 0});
            events.push_back({intervals[i][1], 1});
        }

        sort(events.begin(), events.end());

        // count of open. instead of stack just track #
        int open = 0;
        int i_start = -1;
        
        for (int i = 0; i < events.size(); i++) {
            auto [position, type] = tie(events[i][0], events[i][1]);

            // start
            if (type == 0) {
                if (open == 0) {
                    i_start = position;
                }
                
                open++;
            } else if (type == 1) { //end
                open--;

                if (open == 0) {
                    res.push_back({i_start, position});
                }
            }
        }

        return res;
    }
};
// divergences:
// - I needed tie() to use vector as event
// - realize that tiebreaking is NOT universally: end comes before start. it depends if we want to merge ties or keep them distinct.