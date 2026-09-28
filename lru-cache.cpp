// O(logn) Priority Queue solution. It's cool but this doesn't meet the O(1) constraints.
class LRUCache {
    // min heap, with the weight being the earliest time seen and the value being key
    // hashmap with key:value
    int cap;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    unordered_map<int, int> map;     // key -> value
    unordered_map<int, int> latest;  // key -> latest timestamp
    int t = 0;
public:
    LRUCache(int capacity) {
        cap = capacity;
        pq = priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>();
        map = unordered_map<int, int>();
        t = 0;
    }
    
    // TC: O(logn)
    int get(int key) {
        if (map.contains(key)) {
            // update pq weighting
            latest[key] = t;
            pq.push({t++, key});
            return map[key];
        } else {
            return -1;
        }
    }
    
    // TC: O(logn)
    void put(int key, int value) {
        if (!map.contains(key) && map.size() == cap) {
            // lazy delete stale heap entries
            while (!pq.empty()) {
                auto [time, oldKey] = pq.top();

                if (!latest.contains(oldKey) || latest[oldKey] != time) {
                    pq.pop();
                } else {
                    break;
                }
            }

            auto [time, lruKey] = pq.top();
            pq.pop();

            map.erase(lruKey);
            latest.erase(lruKey);
        }
        map[key] = value;
        latest[key] = t;
        pq.push({t++, key});
    }
};
// divergences:
// - forgot greater<int> syntax
// - used greater int instead of greater pair int int
// - thought I could reserve capacity for pq but i guess not
// - didnt commit to time idea

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */