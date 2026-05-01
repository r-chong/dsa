class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        std::priority_queue<int> pq;

        // loop through all stones and add to priority queue
        for (int s : stones) {
            pq.push(s);
        }

        // Shrink PQ until size < 2
        while (pq.size() >= 2) {
            // heaviest stone
            int y = pq.top();
            pq.pop();

            int x = pq.top();
            pq.pop();

            if (x != y) {
                pq.push(y - x);
            }
        }
        
        // Empty case
        if (pq.empty()) {
            return 0;
        }

        return pq.top();
    }
};