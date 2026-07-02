// push:   TC O(1) amortized, SC O(1) extra per push
// pop:    TC O(1), SC O(1)
// top:    TC O(1), SC O(1)
// getMin: TC O(1), SC O(1)
class MinStack {
    vector<int> arr;
    vector<int> mins;
public:
    MinStack() = default;
    
    void push(int value) {
        arr.push_back(value);

        if (!mins.empty()) {
            mins.push_back(min(getMin(), value));
        } else {
            mins.push_back(value);
        }
    }
    
    void pop() {
        arr.pop_back();
        mins.pop_back();
    }
    
    int top() {
        int n = arr.size();
        return arr[n - 1];
    }
    
    int getMin() {
        int n = mins.size();
        return mins[n - 1];
    }
};
// divergences:
// - originally did this problem with unnecessary tracking of last item, and tried to keep a priority queue of mins etc
// - Then I got an access on empty arr error with getMin in push(). We note that push can have an empty stack but the others can't. I commented out that entire line and falsely assumed that since the program still didn't work without it, that that line wasn't the problem. But it turned out, it was the SAME error but different location; just commenting out doesn't work, as the min still remains empty except it's in later calls (since it's never updated)
// - I also went through godbolt for the first time but couldn't figure out how to read it
// - When calculating time and space complexity for these OOP type problems, you do it per function