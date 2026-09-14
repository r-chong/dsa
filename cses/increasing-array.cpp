#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long prev = 1;
    long long x;
    long long minMoves = 0;
    
    while (cin >> x) {
        long long delta = prev - x;

        if (delta > 0) {
            // if delta is positive, then we must increase to prev
            minMoves += delta;
        } else {
            prev = x;
        }
    }

    cout << minMoves;
    return 0;
}
// divergences:
// - only update prev when we have no difference