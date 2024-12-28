/*
Examples
Input
5
2
4 0
3 1
0
1
2 0
2
3 1
5 1
0

Output
4

*/

#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MOD 998244353

vector<vector<pair<int, int>>> graph;
vector<int> Z;
int N;

void dfs(int v) {
    for (auto &edge : graph[v]) {
        int to = edge.first;
        int w = edge.second;
        Z.push_back(w);
        dfs(to);
    }
}

int count_inversions() {
    int inv_count = 0;
    for (int i = 0; i < Z.size(); i++) {
        for (int j = i + 1; j < Z.size(); j++) {
            if (Z[i] > Z[j]) inv_count++;
        }
    }
    return inv_count % MOD;
}

int main() {
    cin >> N;
    graph.resize(N);

    for (int i = 1; i < N; i++) {
        int M;
        cin >> M;
        for (int j = 0; j < M; j++) {
            int L, W;
            cin >> L >> W;
            graph[i].push_back({L, W});
        }
    }

    // Perform dfs from vertex 1
    dfs(1);

    // Count the number of inversions
    int result = count_inversions();

    // Output the result modulo 998244353
    cout << result << endl;

    return 0;
}
