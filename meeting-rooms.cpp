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
    bool canAttendMeetings(vector<Interval>& intervals) {
        // metadata: [type (0 is end, 1 is start)]
        vector<pair<int, int>> events;

        for (int i = 0; i < intervals.size(); i++) {
            events.push_back({intervals[i].start, 1});
            events.push_back({intervals[i].end, 0});
        }

        sort(events.begin(), events.end());

        for (auto& [pos, type] : events) {
            cout << pos << " " << type << ", ";
        }
        cout << "\n";

        bool meetingOpen = false;

        for (auto& [pos, type] : events) {
            if (type == 1) {
                meetingOpen = false;
            } else if (type == 0) {
                // meeting already happening
                if (meetingOpen) return false;

                meetingOpen = true;
            } 
        }

        return true;
    }
};
// divergences
// - did not consider start of one interval == end of another
// - ordering of sort turned out to be wrong. I set the comparator to be 0 == start and 1 == end because that made sense to me. But with sorting semantics, 0 naturally goes before 1. My goal is to have start, end, start even where end == start. therefore set end to be a value and start to be greater than start