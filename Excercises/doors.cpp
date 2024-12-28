#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void solve() {
    long long a, b, c, d;
    cin >> a >> b >> c >> d;

    long long ans = 0;
    
    if (a > d || c > b) {
        ans = 1;
    }
    else if (a == d || b == c) {
        ans = 2;
    }
    else if (a > c) {
        if (d < b) {
            ans = d - a + 1 + 1;
        }
        else if (d == b) {
            ans = b - a + 1 + 0;
        }
        else if (d > b) {
            ans = b - a + 1 + 1;
        }
    }
    else if (a == c) {
        if (d < b) {
            ans = d - a + 0 + 1;
        }
        else if (d == b) {
            ans = b - a + 0 + 0;
        }
        else if (d > b) {
            ans = b - a + 0 + 1;
        }
    }
    else if (a < c) {
        if (d < b) {
            ans = d - c + 1 + 1;
        }
        else if (d == b) {
            ans = d - c + 1 + 0;
        }
        else if (d > b) {
            ans = b - c + 1 + 1;
        }
    }

    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
