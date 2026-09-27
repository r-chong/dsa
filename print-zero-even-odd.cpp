class ZeroEvenOdd {
private:
    int n;

    mutex mtx;

    condition_variable cv;

    // 0 = zero
    // 1 = odd
    // 2 = even
    int state = 0;
    int current = 1;

    // we start with 0
public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i++) {
            unique_lock<mutex> lock(mtx);

            cv.wait(lock, [&]{
                return state == 0 || current > n;
            });

            printNumber(0);

            // control the next. Only zero determines the next. Even,odd MUST go to 0
            if (current % 2 == 1) {
                state = 1;
            } else {
                state = 2;
            }
            
            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        while (true) {
            unique_lock<mutex> lock(mtx);

            cv.wait(lock, [&]{
                return state == 2 || current > n;
            });

            if (current > n) {
                cv.notify_all();
                return;
            }

            printNumber(current);
            current++;
            state = 0;

            cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        while (true) {
            unique_lock<mutex> lock(mtx);

            cv.wait(lock, [&]{
                return state == 1 || current > n;
            });

            if (current > n) {
                cv.notify_all();
                return;
            }

            printNumber(current);
            current++;
            state = 0;

            cv.notify_all();
        }
    }
};
// divergences:
// - reached for but forgot condition variable, and the syntax for wait
// - didnt understand cpp lambda reference (if it copied the variables by value, would never change and wait forever)
// - didn't consider current > n as a shutdown for cv.wait() else threads hang
// - I thought unique lock was something special that you do once per thread not that you could put it in a loop
// - was allowing printing on current > n