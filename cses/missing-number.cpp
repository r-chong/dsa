#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int x = n;
    int val;

    for (int i = 1; i < n; i++) {
        cin >> val;
        x ^= val;
        x ^= i;
    }

    cout << x << "\n";

    return 0;
}