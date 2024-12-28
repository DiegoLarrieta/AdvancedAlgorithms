#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int mood = 1000000007;

vector<int> par, sze;

void initialize(int n) {
    par.resize(n + 1);
    sze.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        par[i] = i;
        sze[i] = 1;
    }
}

int find(int a) {
    if(par[a] == a) {
        return a;
    } else {
        return (par[a] = find(par[a])); // Path compression
    }
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if(a == b) return;
    if(sze[a] < sze[b]) {
        swap(a, b);
    }
    par[b] = a;
    sze[a] += sze[b];
}

long long power(long long x, unsigned long long y, long long p) {
    long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % p;
        }
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

void solve() {
    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;
        initialize(n);

        vector<int> a(n + 1), b(n + 1), c(n + 1);

        for(int i = 1; i <= n; i++) cin >> a[i];
        for(int i = 1; i <= n; i++) cin >> b[i];
        for(int i = 1; i <= n; i++) cin >> c[i];

        for(int i = 1; i <= n; i++) {
            merge(a[i], b[i]);
            if(a[i] == b[i]){
              c[i] = b[i];
            }
        }

        set<int> s;
        for(int i = 1; i <= n; i++) {
            s.insert(find(i));
        }

        for(int i = 1; i <= n; i++) {
            if(c[i]) {
                s.erase(find(c[i]));
            }
        }

        cout << power(2, s.size(), mood) << "\n";
    }
}

int main() {
    solve();
    return 0;
}
