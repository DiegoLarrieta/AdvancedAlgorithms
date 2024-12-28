/*
Input 
4 5
1 2 3
2 4 2
1 3 4
3 4 5
4 1 3

Sample Output
The maximum speed is 6.
*/ 

// Luis Diego Dominguez Larrieta A01275640
#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <algorithm>

using namespace std;

struct Edge {
    int v;            // Nodo destino
    long long flow;   // Flujo actual
    long long C;      // Capacidad de la arista
    int rev;          // Índice de la arista inversa
};

class Graph {
    int V;                // Número de vértices
    int* level;           // Niveles de los nodos
    vector<Edge>* adj;    // Lista de adyacencia

public:
    Graph(int V) {
        adj = new vector<Edge>[V];
        this->V = V;
        level = new int[V];
    }
    //Complejidad O(1)
    void addEdge(int u, int v, long long C) {
        Edge a{v, 0, C, (int)adj[v].size()};
        Edge b{u, 0, 0, (int)adj[u].size()};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }

    bool BFS(int s, int t);
    long long sendFlow(int s, long long flow, int t, int start[]);
    long long DinicMaxflow(int s, int t);
};

//Complejidad O(V + E)
bool Graph::BFS(int s, int t) {
    for (int i = 0; i < V; i++)
        level[i] = -1;

    level[s] = 0;
    list<int> q;
    q.push_back(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();

        for (auto& e : adj[u]) {
            if (level[e.v] < 0 && e.flow < e.C) {
                level[e.v] = level[u] + 1;
                q.push_back(e.v);
            }
        }
    }

    return level[t] >= 0;
}
//Complejidad O(E)
long long Graph::sendFlow(int u, long long flow, int t, int start[]) {
    if (u == t)
        return flow;

    for (; start[u] < adj[u].size(); start[u]++) {
        Edge& e = adj[u][start[u]];

        if (level[e.v] == level[u] + 1 && e.flow < e.C) {
            long long curr_flow = min(flow, e.C - e.flow);
            long long temp_flow = sendFlow(e.v, curr_flow, t, start);

            if (temp_flow > 0) {
                e.flow += temp_flow;
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}
//Complejidad O(E*V^2)
long long Graph::DinicMaxflow(int s, int t) {
    if (s == t)
        return -1;

    long long total = 0;

    while (BFS(s, t)) {
        int* start = new int[V + 1]{0};

        while (long long flow = sendFlow(s, LLONG_MAX, t, start))
            total += flow;

        delete[] start;
    }
    return total;
}

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        g.addEdge(a - 1, b - 1, c);
    }

    long long maxFlow = g.DinicMaxflow(0, n - 1);
    cout << "The maximum speed is " << maxFlow << "." << endl;

    return 0;
}
