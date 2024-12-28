//
// Matricula: Luis Diego Dominguez Larrieta   
// Nombre: A01275640
//

#include <iostream>
#include <vector>
#include <climits>
#define INF INT_MAX 
using namespace std;

struct edge {
    int from, to, time;
    edge(int a, int b, int t) {
        from = a;
        to = b;
        time = t;
    }
};

struct comm {
    char query;
    int from, to;
    comm(char q, int a, int b) {
        query = q;
        from = a;
        to = b;
    }
};

// Función para calcular el camino mínimo usando Floyd-Warshall O(N^3)
void floydWarshall(int n, vector<vector<int>>& dist) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

void ejecuta_comandos(int n, vector<edge>& edges, vector<comm>& commands, vector<int>& salida) {
    // Inicializar la matriz de distancias con infinito
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));

    // La distancia de un punto a sí mismo es 0
    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
    }

    // Llenar la matriz con las distancias iniciales de las calles
    for (auto& e : edges) {
        dist[e.from][e.to] = e.time;
        dist[e.to][e.from] = e.time; // Es una calle bidireccional
    }

    // Aplicar el algoritmo de Floyd-Warshall para calcular distancias mínimas iniciales
    floydWarshall(n, dist);

    for (auto& c : commands) {
        if (c.query == 'c') {
            
            if (dist[c.from][c.to] == INF) {
                salida.push_back(-1); 
            } else {
                salida.push_back(dist[c.from][c.to]);
            }
        } else if (c.query == 'a') {
            // Bloquear temporalmente la calle entre c.from y c.to
            dist[c.from][c.to] = INF;
            dist[c.to][c.from] = INF;

            // Recalcular toda la matriz de distancias usando Floyd-Warshall
            // después de bloquear la calle para reflejar los cambios
            floydWarshall(n, dist);
        }
    }
}

int main(){
  int n, m, k,a, b, t;
  char q;
  vector<edge> edges;
  vector<comm> commands;
  cin >> n >> m;
  for (int i=1; i<=m; i++){
    cin >> a >> b >> t;
    edge nuevo(a, b, t);
    edges.push_back(nuevo);
  }
  cin >> k;
  for (int i=1; i<=k; i++){
    cin >> q >> a >> b;
    comm nuevo(q, a, b);
    commands.push_back(nuevo);
  }
  vector<int> salida;
  ejecuta_comandos(n, edges, commands, salida);
    for (int i=0;i<salida.size(); i++){
      cout << salida[i]<< endl;
    }
}
