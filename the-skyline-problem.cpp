class Solution {
public:
    // TC: O(nlogn), SC: O(n)
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        // [position, type, height, end]
        vector<vector<int>> pts;
        vector<vector<int>> res;

        for (auto& b : buildings) {
            pts.push_back({b[0], 0, b[2], b[1]});
            pts.push_back({b[1], 1, 0, 0});
        }

        sort(pts.begin(), pts.end());

        // interestingly we don't keep position in the heap, just need 
        // [height, end] what about also expired] - expired 0 is false 1 is true
        priority_queue<vector<int>> mh;

        // could do result.back()[1]
        int prevHeight = 0;
        int height = 0;
        int i = 0;

        while (i < pts.size()) {
            int x = pts[i][0];

            // invalidate buildings that are now expired
            while (!mh.empty() && mh.top()[1] <= x) {
                mh.pop();
            }

            // add buildings that are now in view
            while (i < pts.size() && pts[i][0] == x) {
                // if is the front part of the building, add [height, end]
                if (pts[i][1] == 0) {
                    mh.push({pts[i][2], pts[i][3]});
                }
                i++;
            }

            if (mh.empty()) {
                height = 0;
            } else {
                height = mh.top()[0];
            }

            // see if height changed
            if (res.empty() || height != prevHeight) {
                res.push_back({x, height});
            }
            prevHeight = height;
        }

        return res;
    }
};
// divergences:
// - wanted to reach for - is this valid         for (vector<int>& [left, right, height] : buildings) 
// - forget if CPP is max heap or min heap
// - needed to verify that top() is how you get max in max heap
// - it doesn't make sense!!!
// - my ordering of everything happening was wrong
// - could not work with ranged based for loop
// - didnt add the RHS of sweepline for some reason

// revisions:
// - didn't need to store redundant information; can have different fields if i gate on type==

// divergences(mindsolve):
// - was too granular tried to enumerate left/right edge cases individually

// More exercises:
// - Sweepline + multiset