#include <bits/stdc++.h>
using namespace std;

int main() {
    char c;

    // b is invalid
    char prev = 'B';
    long long maxStreak = 1;
    long long streak = 1;

    while (cin >> c) {
        if (c == prev) {
            streak++;
        } else {
            streak = 1;
        }

        prev = c;
        maxStreak = max(maxStreak, streak);
    }

    cout << maxStreak;
    return 0;
}
// divergences:
// - off by one
// - AAAAAA is not all one input
// - was putting max in wrong spot