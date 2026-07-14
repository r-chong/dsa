// Attempt 1 (on my own!) ~1h
class TimeMap {
    // key: list of <timestamps, hash>
    // SC: O(k * v)
    // where k = number of keys, v = the number of values
    unordered_map<string, vector<pair<int, string>>> ktv;
public:
    TimeMap() = default;
    
    // TC: O(1) average, amortized
    void set(string key, string value, int timestamp) {
        ktv[key].push_back({timestamp, value});
    }
    
    // TC: O(n)
    string get(string key, int timestamp) {
        // search kth[key] and find the value before it
        // if no values before it then return ""

        int n = ktv[key].size();

        // "" if no values
        // short circuit if timestamp is later than last valid timestamp
        if (n == 0) return "";
        if (timestamp > ktv[key][n - 1].first) {
            return ktv[key][n - 1].second;
        }

        // the first "prev" is the first timestamp
        int timestamp_prev = ktv[key][0].first;
        string timestamp_prev_val = ktv[key][0].second;

        // short circuit if we request prior to first timestamp
        if (timestamp_prev > timestamp) {
            return "";
        } 

        // loop through all <timestamps, val>
        // if find the timestamp, return that one
        // else return the LARGEST one before it
        for (auto& [ts, val] : ktv[key]) {
            if (ts == timestamp) {
                return val;
            } else if (ts > timestamp) {
                break;
            }

            if (ts > timestamp_prev) {
                timestamp_prev_val = val;
            }
        }
        
        return timestamp_prev_val;
    }
};
// divergences:
// - started with two hash maps unnecessarily
// - thought I had to hash  
//      - needed to learn hash<>{}() syntax
// - missed upper and lower edge cases at first (but figured it out)

// optimal solution:
class TimeMap {
    // key: list of <timestamps, hash>
    // SC: O(k * v)
    // where k = number of keys, v = the number of values
    unordered_map<string, vector<pair<int, string>>> ktv;
public:
    TimeMap() = default;
    
    // TC: O(1)
    void set(string key, string value, int timestamp) {
        ktv[key].push_back({timestamp, value});
    }
    
    // TC: O(logn)
    string get(string key, int timestamp) {
        // search kth[key] and find the value before it
        // if no values before it then return ""

        int n = ktv[key].size();

        // "" if no values
        // short circuit if timestamp is later than last valid timestamp
        if (n == 0) return "";
        if (timestamp > ktv[key][n - 1].first) {
            return ktv[key][n - 1].second;
        }

        // the first "prev" is the first timestamp
        int timestamp_prev = ktv[key][0].first;
        string timestamp_prev_val = ktv[key][0].second;

        // short circuit if we request prior to first timestamp
        if (timestamp_prev > timestamp) {
            return "";
        } 

        // binary search <timestamps, val>
        // if find the timestamp, return that one
        // else return the LARGEST one before it
        int lo = 0;
        int hi = n;

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            int ts = ktv[key][mid].first;

            if (ts > timestamp) {
                hi = mid;
            } else {
                lo = mid + 1;
            }

            // more idiomatic way of doing it - put the OK() condition first
            // if (ts <= timestamp) {
            //     lo = mid + 1;
            // } else {
            //     hi = mid;
            // }
        }
        
        // right has converged to the left; no values satisfying <= timestamp / all values of ts are greater than requested        
        if (lo == 0) return "";

        return ktv[key][lo - 1].second;
    }
};
// divergences:
// - I thought my predicate was, is == target? but I want it to always be true that we are <= target
// - so i had put the equals case in the else invisibly

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */