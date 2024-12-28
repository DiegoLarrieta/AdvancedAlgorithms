/*
Luis Diego Dominguez Larrieta
A01275640
*/

#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

#define MAX 100
#define INF INT_MAX

// Define types for graph representation
typedef pair<int, int> Edge; // Represents (destination, weight)
typedef vector<vector<Edge>> Graph; // Adjacency list representation
typedef pair<int, int> Vertex; // Represents (distance, node)

void leeArcos(int matAdj[MAX][MAX], int nodes, int edges, Graph &listAdj) {
    int u, v, w;
    // Initialize the adjacency matrix
    for (int i = 0; i < nodes; i++) {
        matAdj[i][i] = 0;
        for (int j = i + 1; j < nodes; j++) {
            matAdj[i][j] = matAdj[j][i] = INF;
        }
    }
    // Read edges
    for (int i = 0; i < edges; i++) {
        cin >> u >> v >> w;
        matAdj[u - 1][v - 1] = matAdj[v - 1][u - 1] = w;
        Edge e1(v - 1, w);
        listAdj[u - 1].push_back(e1);
        Edge e2(u - 1, w);
        listAdj[v - 1].push_back(e2);
    }
}

void print(int matAdj[MAX][MAX], int nodes, Graph &listAdj) {
    // Print adjacency matrix
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            cout << matAdj[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl << "--------" << endl;

    // Print adjacency list
    for (int i = 0; i < nodes; i++) {
        cout << (i + 1) << "====>";
        for (int j = 0; j < listAdj[i].size(); j++) {
            cout << "(" << listAdj[i][j].first + 1 << " , " << listAdj[i][j].second << ")";
        }
        cout << endl;
    }
}

void printOutput(int matAdj[MAX][MAX], int nodes, int source, vector<int> &dist) {
    cout << "Floyd" << endl;
    for (int j = 0; j < nodes; j++) {
        if (j != source - 1) {
            cout << source << " --> " << (j + 1) << " : " << matAdj[source - 1][j] << endl;
        }
    }
    cout << "Dijkstra" << endl;
    for (int j = 0; j < nodes; j++) {
        if (j != source - 1) {
            cout << source << "--->" << (j + 1) << " : " << dist[j] << endl;
        }
    }
}

void floyd(int matAdj[MAX][MAX], int nodes) {
    for (int k = 0; k < nodes; k++) {
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                if (matAdj[i][k] != INF && matAdj[k][j] != INF && matAdj[i][k] + matAdj[k][j] < matAdj[i][j]) {
                    matAdj[i][j] = matAdj[i][k] + matAdj[k][j];
                }
            }
        }
    }
}

vector<int> dijkstra(Graph &listAdj, int source) {
    vector<int> dist(listAdj.size(), INF);
    dist[source - 1] = 0;
    priority_queue<Vertex, vector<Vertex>, greater<Vertex>> queue;
    queue.push({0, source - 1});

    while (!queue.empty()) {
        int u = queue.top().second;
        queue.pop();
        for (const Edge &e : listAdj[u]) {
            int v = e.first;  // Destination node
            int w = e.second; // Edge weight
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                queue.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    int nodes, edges, source;
    int matAdj[MAX][MAX];

    cin >> nodes >> edges >> source;

    Graph listAdj(nodes); // Initialize the adjacency list

    leeArcos(matAdj, nodes, edges, listAdj);

    floyd(matAdj, nodes);
    vector<int> dist = dijkstra(listAdj, source);

    //print(matAdj, nodes, listAdj);
    printOutput(matAdj, nodes, source, dist);

    return 0;
}

/*
7 9 3
1 2 50
1 3 60
2 4 120
2 5 90
3 6 50
4 6 80
4 7 70
5 7 40
6 7 140
*/