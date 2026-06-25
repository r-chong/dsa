#include <stdexcept>

// Stack using LList
struct Node {
    Node* next;
    int val;

    Node(int val) {
        next = nullptr;
        this->val = val;
    }
};

// TC: O(1) for all operations
class Stack {
private:
    Node* head;
    int size = 0;

public:
    Stack() {
        head = nullptr;
    }

    ~Stack() {
        while (head != nullptr) {
            Node* temp = head->next;
            delete head;
            head = temp;
        }
    }

    // Disable for safety, as big 5 is not the focus of this exercise
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(int a) {
        Node* n = new Node(a);
        size++;
        n->next = head;
        head = n;
    }

    int pop() {
        if (head == nullptr) throw std::runtime_error("pop from empty stack");

        int val = head->val;
        Node* temp = head->next;

        delete head;
        head = temp;

        size--;

        return val;
    }

    int top() {
        if (head == nullptr) throw std::runtime_error("top from empty stack");
        return head->val;
    }

    bool empty() {
        return (head == nullptr);
    }

    int getSize() {
        return this->size;
    }
};

// 2. Stack using dynamic array
//    - Practice capacity, resizing, size tracking.
//    - Harder version: don't use vector internally.
//
// 3. Stack using two queues
//    - LeetCode 225.
//    - Easier conceptual version.
//
// 4. Stack using one queue
//    - LeetCode 225 harder version.
//    - Best version for forcing the invariant.