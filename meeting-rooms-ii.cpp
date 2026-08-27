/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        vector<vector<int>> events;

        // 0 is end
        // 1 will be start
        // therefore we don't care about merges

        for (int i = 0; i < intervals.size(); i++) {
            events.push_back({intervals[i].start, 1});
            events.push_back({intervals[i].end, 0});
        }

        sort(events.begin(), events.end());

        int maxConcurrent = 0;
        int concurrent = 0;
        
        for (int i = 0; i < events.size(); i++) {
            // start
            if (events[i][1] == 1) {
                concurrent++;
                maxConcurrent = max(maxConcurrent, concurrent);
            } else {
                // end
                concurrent--;
            }   
        }

        return maxConcurrent;
    }
};
