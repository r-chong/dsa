class Foo {
    bool first_done = false;
    bool second_done = false;

    std::mutex m_;
    std::condition_variable cv;
public:
    Foo() {
        
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();

        {
            std::lock_guard<std::mutex> lock(m_);
            first_done = true;
        }

        cv.notify_all();
    }

    void second(function<void()> printSecond) {

        {
            std::unique_lock<std::mutex> lock(m_);

            cv.wait(lock, [this] {
                return first_done;
            });
        }
        
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();

        {
            std::lock_guard<std::mutex> lock(m_);
            second_done = true;
        }

        cv.notify_all();
    }

    void third(function<void()> printThird) {

        {
            std::unique_lock<std::mutex> lock(m_);

            cv.wait(lock, [this] {
                return second_done;
            });
        }
        
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};
// divergences:
// - the condition checker is a unique lock not lock guard