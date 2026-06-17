class max_heap {
    private:
    std::vector<int> bt;
    int size;

    int indexOfParent(int c) {
        return (c - 1) / 2;
    }

    public:
    max_heap(int size) {
        bt.reserve(size);
    }

    void push(int ele) {
        bt.push_back(ele);
                
        int c = (bt.size() - 1);
        
        while (c > 0) {
            int p = indexOfParent(c);

            // max heap invariant is parent >= ele. stop when valid.
            if (bt[p] >= bt[c]) {
                break;
            }

            std::swap(bt[p], bt[c]);
            
            c = p;
        }

        cout << "bt now valid" << endl;
    }

    // CURRENTLY BROKEN. Feedback: After removing the root, you need to sift down from index 0, not bubble up from the last index.
    void pop() {
        // swap first and last
        std::swap(bt[0], bt[this->size - 1]);
        bt.pop_back();

        int c = (bt.size() - 1);

        while (c > 0) {
            int p = indexOfParent(c);

            if (bt[p] >= bt[c]) {
                break;
            }

            std::swap(bt[p], bt[c]);
            
            c = p;
        }
    }

    int top() {
        if (this->bt.empty()) {
            return -1;
        } else {
            return bt[0];
        }
    }

    // TC: O(nlogn), SC: O(n)
    // naive version
    max_heap heapify(std::vector<int> &arr) {
        max_heap::max_heap heap(arr.size());

        for (int i = 0; i < arr.size() - 1; i++) {
            heap.push(arr[i]);
        }

        return heap;
    }
}