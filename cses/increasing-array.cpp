#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long min = 1;
    long long x;
    long long minMoves = 0;
    
    while (cin >> x) {
        long long delta = min - x;

        if (delta > 0) {
            // if delta is positive, then we must increase to prev
            minMoves += delta;
        } else {
            min = x;
        }
    }

    cout << minMoves;
    return 0;
}
// divergences:
// - only update prev in the else bc prev is supposed to represent the value of the previous element after you've made any required increases
// - so if we update it on every move then we're setting a value that should not actually be the prev
// - we're forcing a global minimum