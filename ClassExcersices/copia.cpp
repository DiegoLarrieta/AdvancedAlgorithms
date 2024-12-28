#include <iostream>
#include <vector>
using namespace std;

vector<int> parent, depth, position_in_order;
vector<vector<int>> tree;

// Recursively calculate the depth for each node
void calculate_depths(int node, int dep) {
    depth[node] = dep;
    for (int child : tree[node]) {
        calculate_depths(child, dep + 1);
    }
}

// Check if the current permutation is a valid DFS order
bool is_valid_dfs_order(const vector<int>& perm) {
    for (int i = 2; i < perm.size(); i++) {
        if (position_in_order[parent[perm[i]]] > position_in_order[perm[i]]) {
            return false;
        }
    }
    return true;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;

        parent.resize(n + 1);
        depth.resize(n + 1);
        position_in_order.resize(n + 1);
        tree.assign(n + 1, vector<int>());

        // Read parent-child relationships
        for (int i = 2; i <= n; ++i) {
            cin >> parent[i];
            tree[parent[i]].push_back(i); // build the tree
        }

        vector<int> perm(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> perm[i];
            position_in_order[perm[i]] = i;
        }

        // Calculate the depths starting from the root (node 1)
        calculate_depths(1, 0);

        for (int i = 0; i < q; ++i) {
            int x, y;
            cin >> x >> y;

            // Swap the elements
            swap(perm[x], perm[y]);
            position_in_order[perm[x]] = x;
            position_in_order[perm[y]] = y;

            // Check if the current permutation is a valid DFS order
            if (is_valid_dfs_order(perm)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}
