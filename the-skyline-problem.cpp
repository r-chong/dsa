class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        // [position, height, end]
        // interestingly we don't keep position in the heap, just need 
        vector<vector<int>> pts;

        for (vector<int>& [left, right, height] : buildings) {
            pts.push_back({left, height, right});
        }

        sort(pts.begin(), pts.end());

        // priority_queue<pair<int, int>>
        // max heap
        priority_queue<vector<int>> mh;

        // add to mh
        // check just added value, if we should add a new point
        // not sure the expiration logic here
        

        for (vector<int>& p : pts) {
            // derive the logic here

            // add
            // expire
            // modify
        }
    }
};
// divergences:
// - wanted to reach for - is this valid         for (vector<int>& [left, right, height] : buildings) 
// - forget if CPP is max heap or min heap

// divergences(mindsolve):
// - was too granular tried to enumerate left/right edge cases individually

// More exercises:
// - Sweepline + multiset