/*
Input
5 6
0 1 5
1 4 1
0 4 10
0 2 2
1 2 3
2 3 4
2
2 4
0 1

Output
3
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;

struct Edge {
    int to, length;
};

vector<vector<Edge>> graph;
int n, m, s;
vector<int> stores, kids;

// Dijkstra's algorithm to find shortest paths from a start city to all other cities
vector<int> dijkstra(int start) {
    vector<int> dist(n, INF);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});  // (distance, city)
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int city = pq.top().second;
        pq.pop();
        
        if (d > dist[city]) continue;
        
        for (Edge edge : graph[city]) {
            int next_city = edge.to;
            int next_dist = d + edge.length;
            
            if (next_dist < dist[next_city]) {
                dist[next_city] = next_dist;
                pq.push({next_dist, next_city});
            }
        }
    }
    
    return dist;
}

int main() {
    // Step 1: Input Parsing
    cin >> n >> m;
    graph.resize(n);
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }
    
    cin >> s;
    stores.resize(s);
    for (int i = 0; i < s; i++) {
        cin >> stores[i];
    }
    
    kids.resize(2);
    cin >> kids[0] >> kids[1];
    
    // Step 2: Calculate shortest distances from both kids and stores
    vector<int> dist_from_kid1 = dijkstra(kids[0]);
    vector<int> dist_from_kid2 = dijkstra(kids[1]);
    
    // Step 3: Calculate shortest distance from stores
    vector<vector<int>> dist_from_stores(s);
    for (int i = 0; i < s; i++) {
        dist_from_stores[i] = dijkstra(stores[i]);
    }
    
    // Step 4: Try all store combinations for both kids
    int min_distance = INF;
    
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            int distance = dist_from_kid1[stores[i]] + dist_from_kid2[stores[j]];
            if (distance < min_distance) {
                min_distance = distance;
            }
        }
    }
    
    // Step 5: Output the result
    cout << min_distance << endl;
    
    return 0;
}
