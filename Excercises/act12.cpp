#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
/*
Luis Diego Dominguez Larrieta 
Complejidad O(E LOG E) E number of edges
*/

using namespace std;


struct Edge {
    int u, v; // Indices of the two freckles (points)
    double weight; // Distance between the two freckles

    // Comparator for sorting edges by weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Disjoint Set (Union-Find) for Kruskal's Algorithm
class DisjointSet {
public:
    vector<int> parent, rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void union_sets(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);

        if (root_u != root_v) {
            if (rank[root_u] > rank[root_v]) {
                parent[root_v] = root_u;
            } else if (rank[root_u] < rank[root_v]) {
                parent[root_u] = root_v;
            } else {
                parent[root_v] = root_u;
                rank[root_u]++;
            }
        }
    }
};

// Function to calculate the Euclidean distance between two points (freckles)
double calculate_distance(pair<double, double> point1, pair<double, double> point2) {
    return sqrt(pow(point1.first - point2.first, 2) + pow(point1.second - point2.second, 2));
}

int main() {
    int n;
    cin >> n;

    // Special case: if there are no freckles, output 0.00
    if (n == 0) {
        cout << "0.00" << endl;
        return 0;
    }

    // Reading the coordinates of the freckles
    vector<pair<double, double>> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    // Prepare all edges: distance between every pair of freckles
    vector<Edge> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double distance = calculate_distance(points[i], points[j]);
            edges.push_back({i, j, distance});
        }
    }

    // Sort edges by their weight (distance)
    sort(edges.begin(), edges.end());

    // Apply Kruskal's algorithm to find the MST
    DisjointSet ds(n);
    double mst_weight = 0.0;
    int edges_in_mst = 0;

    for (const auto& edge : edges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            ds.union_sets(edge.u, edge.v);
            mst_weight += edge.weight;
            edges_in_mst++;

            // If we've added n-1 edges, we can stop (since it's a connected MST)
            if (edges_in_mst == n - 1) {
                break;
            }
        }
    }

    // Output the total weight of the MST rounded to two decimal places
    cout << fixed << setprecision(2) << mst_weight << endl;

    return 0;
}
