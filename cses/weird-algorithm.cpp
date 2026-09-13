#include <bits/stdc++.h>
using namespace std;
 
void w_alg(long long n) {
    cout << n << " ";
    if (n == 1) return;
 
    long long x;
    if (n % 2 == 0) {
        x = n / 2;
    } else {
        x = n * 3 + 1;
    }
    w_alg(x);
}
 
int main() {
    long long n;
    cin >> n;
 
    w_alg(n);
 
    return 0;
}
// thoughts:
// - could I do bit shift right to do division by 2, does it work here if non bit manip?
// - is there a similar thing for n*3