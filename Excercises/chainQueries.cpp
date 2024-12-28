/*
Chain Queries
You are given a tree of n vertices numbered from 1 to n, Initually , all vertices are coloured white or blakc

You are asked to perform q queries
-"u" -> Toggle the color of vertex x (if it is white change it to black and vice versa)

After each query, you should answer whether all the black vertices from a chain . That is there exist 
two black vertices such that the simple path between them passes throught all the black vertices and only the black vertices.
Specifically , if there is only one black vertex, they form a chain, if there are no black vertices, theu do not from a chain

Input 
Each test contains multiple test cases. The first line contains the number of test cases t(1<t<10^4)
The description of the test cases follows

The first line of each test case contains two integers n and q (1<n,q<2*10^5)

The second line of each test case contains n integers c1,c2,...,cn(c1 ∈ {0,1}) -> The initial color of the vertices.
c1 denotes the color of vertex i where 0 denotes the color white , and 1 denotes the color black

The n-1 lines follows , each line contains two integers xi, and yi (1<xi,yi<n), indicating an edge between vertices xi and yi, It is guaranteed that edges form a tree

The following q lines each contain an integer ui (1<ui<n) , indicating the color of vertex ui, need to be toggled.

It is guaranteed that the sum of n and q over all test cases respectively does not exceed 2*10^5

Output

For each query, output "Yes" if the black vertices form a chain, and output "No" otherwise.
*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
using namespace std;

vector<int> color;
vector<vector<int>> adj;
unordered_set<int> blackVertices;
unordered_map<int, int> blackDegree;

bool isChain() {
    if (blackVertices.empty()) return false;  // No black vertices
    if (blackVertices.size() == 1) return true;  // Single black vertex is trivially a chain
    
    int endpoints = 0;  // Count of vertices with only one black neighbor
    for (int node : blackVertices) {
        if (blackDegree[node] == 1) {
            endpoints++;
        }
        if (endpoints > 2) return false;  // More than 2 endpoints means not a chain
    }
    
    return endpoints == 2;  // A valid chain should have exactly 2 endpoints
}

void toggleColor(int u) {
    if (color[u] == 1) {
        // Turn black -> white
        color[u] = 0;
        blackVertices.erase(u);
        // Update degree of neighbors
        for (int neighbor : adj[u]) {
            if (blackVertices.count(neighbor)) {
                blackDegree[neighbor]--;
                blackDegree[u]--;
            }
        }
    } else {
        // Turn white -> black
        color[u] = 1;
        blackVertices.insert(u);
        // Update degree of neighbors
        for (int neighbor : adj[u]) {
            if (blackVertices.count(neighbor)) {
                blackDegree[neighbor]++;
                blackDegree[u]++;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);  // Fast IO
    cin.tie(0);  // Untie cin and cout for better performance
    int t;
    cin >> t;
    
    while (t--) {
        int n, q;
        cin >> n >> q;
        
        color.resize(n + 1);
        adj.clear();
        adj.resize(n + 1);
        blackVertices.clear();
        blackDegree.clear();
        
        // Input colors
        for (int i = 1; i <= n; ++i) {
            cin >> color[i];
            if (color[i] == 1) {
                blackVertices.insert(i);
                blackDegree[i] = 0;
            }
        }
        
        // Input edges and build adjacency list
        for (int i = 0; i < n - 1; ++i) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
            // If both vertices are black, increase their black neighbor degree
            if (blackVertices.count(x) && blackVertices.count(y)) {
                blackDegree[x]++;
                blackDegree[y]++;
            }
        }
        
        // Handle queries
        for (int i = 0; i < q; ++i) {
            int u;
            cin >> u;
            toggleColor(u);  // Toggle the color of vertex u
            cout << (isChain() ? "YES" : "NO") << '\n';  // Check if the black vertices form a chain
        }
    }
    
    return 0;
}
