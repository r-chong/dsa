// Linked List solution
// TC: O(1), SC: O(1)
class LRUCache {
    int cap;
    // list in order of least to most recently used
    // the front is LRU and back is MRU
    list<Node> lru;
    // key to a node
    unordered_map<int, list<Node>::iterator> map;
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if (!map.contains(key)) return -1;

        // update LRU
        auto it = map[key];

        // move this node to the front in O(1)
        lru.splice(lru.begin(), lru, it);

        return it->val;
    }
    
    void put(int key, int value) {
        if (map.contains(key)) {
            auto it = map[key];
            it->val = value;
            lru.splice(lru.begin(), lru, it);
            return;
        }

        // only evict when inserting a NEW key
        if (map.size() == cap) {
            int oldKey = lru.back().key;
            lru.pop_back();
            map.erase(oldKey);
        }

        lru.push_front({key, value});
        map[key] = lru.begin();
    }
};
// divergences:
// - didnt know lru.splice(lru.begin(), lru, it);
// - with iterator we seem to use . instead of -> syntax
// - was evicting even if key already exists (no issue with cap)
// - declaration of variable with deduced type 'auto' requires an initializer

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

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