/*
Luis Diego Dominguez Larrieta
A01275640
*/

/*
Input

2
5 7
A B 5
A C 4
A D 7
B E 3
C D 2
C E 4
D E 1
4 6
A B 1
A C 1
A D 1
B C 1
B D 1
C D 1

Output

Case 1: E
Case 2: B

Complejidad 
Constriccion de grafo O(n + k)

Dijkstra O((n + k)log n)

*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;

// Dijkstra's algorithm to find shortest paths from the source node
unordered_map<char, int> dijkstra(unordered_map<char, vector<pair<char, int>>>& graph, char start, int n) {
    unordered_map<char, int> distances;
    // Initialize distances to all nodes as infinity, except the start node
    for (char node = 'A'; node < 'A' + n; node++) {
        distances[node] = INT_MAX;
    }
    distances[start] = 0;

    // Min-heap priority queue to store {distance, node}
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        char current_node = pq.top().second;
        pq.pop();

        // If the current distance is greater than the already found shortest distance, skip it
        if (current_distance > distances[current_node]) {
            continue;
        }

        // Check all neighbors of the current node
        for (auto& neighbor : graph[current_node]) {
            char neighbor_node = neighbor.first;
            int weight = neighbor.second;

            int distance = current_distance + weight;
            // If a shorter path to the neighbor is found
            if (distance < distances[neighbor_node]) {
                distances[neighbor_node] = distance;
                pq.push({distance, neighbor_node});
            }
        }
    }

    return distances;
}

// Solve for each case
char solve_case(int n, vector<tuple<char, char, int>>& connections) {
    unordered_map<char, vector<pair<char, int>>> graph;

    // Build the graph
    for (auto& conn : connections) {
        char u, v;
        int w;
        tie(u, v, w) = conn;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});  // Since the graph is undirected
    }

    // Run Dijkstra's algorithm from Room A
    unordered_map<char, int> distances = dijkstra(graph, 'A', n);

    // Find the room with the longest shortest path
    int max_dist = -1;
    char result_room = 'Z' + 1;  // Use 'Z' + 1 to make sure it is alphabetically larger than any valid room
    for (char room = 'A'; room < 'A' + n; room++) {
        if (room != 'A' && distances[room] != INT_MAX) {  // Skip room A and unreachable rooms
            if (distances[room] > max_dist) {
                max_dist = distances[room];
                result_room = room;
            } else if (distances[room] == max_dist && room < result_room) {
                result_room = room;
            }
        }
    }

    return result_room;
}

int main() {
    int num_cases;
    cin >> num_cases;

    vector<string> results;  // Vector to store the results for each case

    for (int case_num = 1; case_num <= num_cases; case_num++) {
        int n, k;
        cin >> n >> k;

        vector<tuple<char, char, int>> connections(k);
        for (int i = 0; i < k; i++) {
            char u, v;
            int w;
            cin >> u >> v >> w;
            connections[i] = make_tuple(u, v, w);
        }

        // Solve the current case and store the result
        char result_room = solve_case(n, connections);
        results.push_back("Case " + to_string(case_num) + ": " + result_room);
    }

    // Output all results at once
    for (const auto& result : results) {
        cout << result << endl;
    }

    return 0;
}