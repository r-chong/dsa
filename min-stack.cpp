class MinStack {
    vector<int> arr;
    vector<int> mins;
public:
    MinStack() {
        
    }
    
    void push(int val) {
        // keep n mins indices, 
        arr.push_back(val);

        if (!mins.empty()) {
            mins.push_back(min(val, mins.back()));
        } else {
            mins.push_back(val);
        }
    }
    
    void pop() {
        arr.pop_back();
        mins.pop_back();
    }
    
    int top() {
        return arr.back();
    }
    
    int getMin() {
        return mins.back();
    }
};
