class KthLargest {
    priority_queue<int, vector<int>, greater<int>> pq;
    int gk = 0;
public:
    KthLargest(int k, vector<int>& nums) {
        gk = k;

        for (int n : nums) {
            add(n);
        }
    }
    
    int add(int val) {
        pq.push(val);

        if (pq.size() > gk) {
            pq.pop();
        }

        return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

 // divergences: mostly syntax
 // - priority_queue<int, vector<int>, greater<int>> pq; if min_heap which keeps min at the top. then we pop min to keep the higher
 // - priority_queue<int> pq; if max heap which keeps max at the top. which is not this problem
 // - used >= gk instead of >, which meant the size of pq was one less than it was supposed to
 // - didnt read the problem. be more careful