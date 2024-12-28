#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class SparseTable {
public:
    vector<int> log;
    vector<vector<int>> sparse;
    int k;

    SparseTable(const vector<int>& arr) {
        int n = arr.size();
        log.resize(n + 1);
        log[1] = 0;
        for (int i = 2; i <= n; i++) {
            log[i] = log[i / 2] + 1;
        }

        k = log[n];
        sparse.resize(n, vector<int>(k + 1));
        for (int i = 0; i < n; i++) {
            sparse[i][0] = arr[i];
        }

        for (int j = 1; j <= k; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                sparse[i][j] = max(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int getMax(int l, int r) {
        int j = log[r - l + 1];
        return max(sparse[l][j], sparse[r - (1 << j) + 1][j]);
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> arr(m, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[j][i];
        }
    }

    vector<SparseTable> st;
    for (int i = 0; i < m; i++) {
        st.push_back(SparseTable(arr[i]));
    }

    int l = 0, r = 0;
    vector<int> result(m, 0);
    vector<int> ll;

    while (l <= r && r < n) {
        int sum = 0;
        for (int i = 0; i < m; i++) {
            sum += st[i].getMax(l, r);
        }

        if (sum <= k) {
            ll.clear();
            for (int i = 0; i < m; i++) {
                ll.push_back(st[i].getMax(l, r));
            }
            r++;
        } else {
            l++;
            r++;
        }
    }

    if (ll.empty()) {
        for (int i = 0; i < m; i++) {
            cout << 0 << " ";
        }
    } else {
        for (int i = 0; i < m; i++) {
            cout << ll[i] << " ";
        }
    }
    cout << endl;

    return 0;
}
