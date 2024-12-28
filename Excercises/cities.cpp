/*
Input
3 4
1 2 6
1 3 2
3 2 3
1 3 4

Output
0 5 2
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const long long INF = LLONG_MAX;

struct Edge {
    int to;
    long long length;
};

vector<vector<Edge>> graph;
vector<long long> dist;

void dijkstra(int start) {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});  // (distance, city)
    
    while (!pq.empty()) {
        long long d = pq.top().first;
        int city = pq.top().second;
        pq.pop();
        
        // Skip if the current distance is not optimal
        if (d > dist[city]) continue;
        
        // Relax the edges
        for (Edge edge : graph[city]) {
            int next_city = edge.to;
            long long next_dist = d + edge.length;
            
            if (next_dist < dist[next_city]) {
                dist[next_city] = next_dist;
                pq.push({next_dist, next_city});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    graph.resize(n + 1);
    dist.resize(n + 1, INF);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
    }
    
    // Run Dijkstra's algorithm from city 1 (Syrjälä)
    dijkstra(1);
    
    // Output the shortest distances from city 1 to all cities
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    cout << endl;
    
    return 0;
}
