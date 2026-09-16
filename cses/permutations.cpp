#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    if ((n < 4) && (n != 1)) {
        cout << "NO SOLUTION";
        return 0;
    }

    if (n == 4) {
        cout << "2 4 1 3 ";
        return 0;
    }

    for (int i = 1; i <= n; i += 2) {
        cout << i << " ";
    }

    for (int i = 2; i <= n; i += 2) {
        cout << i << " ";
    }
    
    return 0;
}
// divergences:
// - for some reason I thought i could do this in O(1) because it seemed mathy
// - struggled with loop, should have used two
// - didn't hardcode case n=4