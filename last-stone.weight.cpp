// Brute force sort() solution
// TC: O(n^2logn), SC: O(logn) auxilary because std::sort typically uses O(logn) stack space
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        while (stones.size() > 1) {
            std::sort(stones.begin(), stones.end());

            int n = stones.size();
            int last = n - 1;
            int last2 = n - 2;

            if (stones[last] == stones[last2]) {
                stones.pop_back();
                stones.pop_back();
            } else {
                stones[last2] = stones[last] - stones[last2];
                stones.pop_back();
            }
        }

        if (stones.size() == 0) return 0;

        return stones[0];
    }
};
// divergences:
// - used pop instead of pop back for vector
// - set winning stone y to y instead of y - x
// - forgot Return the weight of the last remaining stone. If there are no stones left, return 0.

// Priority queue (max heap)
// TC: O(nlogn), SC: O(n) auxilary
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        std::priority_queue<int> pq(stones.begin(), stones.end());
        
        while (pq.size() > 1) {
            int y = pq.top();
            pq.pop();

            int x = pq.top();
            pq.pop();

            if (x == y) {
                continue;
            } else {
                pq.push(y - x);
            }
        }

        if (pq.size() == 0) return 0;

        return pq.top();
    }
};
// divergences:
// - had to search for top() method of pq
// - forgot to change some stones() impl