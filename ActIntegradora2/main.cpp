/*
Luis Diego Dominguez Larrieta
A01275640
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <queue>
#include <set>

using namespace std;

// Estructuras para representar los datos
struct Colony {
    string name;
    int x, y, isCentral;
};

struct Edge {
    string from, to;
    int cost;
};

// Función para calcular la distancia euclidiana
// Complejidad de O(1)
double euclideanDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Kruskal: Unión-Find
struct UnionFind {
    unordered_map<string, string> parent;
    unordered_map<string, int> rank;

    void makeSet(const string& v) {
        parent[v] = v;
        rank[v] = 0;
    }

    string find(const string& v) {
        if (parent[v] != v) {
            parent[v] = find(parent[v]); // Compresión de caminos
        }
        return parent[v];
    }

    void unite(const string& a, const string& b) {
        string rootA = find(a);
        string rootB = find(b);
        if (rootA != rootB) {
            if (rank[rootA] > rank[rootB]) {
                parent[rootB] = rootA;
            } else if (rank[rootA] < rank[rootB]) {
                parent[rootA] = rootB;
            } else {
                parent[rootB] = rootA;
                rank[rootA]++;
            }
        }
    }
};

// Función para leer la entrada
void readInput(vector<Colony>& colonies, vector<Edge>& edges, vector<Edge>& newCabling, vector<Colony>& newColonies) {
    int n, m, k, q;
    cin >> n >> m >> k >> q;

    colonies.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> colonies[i].name >> colonies[i].x >> colonies[i].y >> colonies[i].isCentral;
    }

    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].from >> edges[i].to >> edges[i].cost;
    }

    newCabling.resize(k);
    for (int i = 0; i < k; ++i) {
        cin >> newCabling[i].from >> newCabling[i].to;
    }

    newColonies.resize(q);
    for (int i = 0; i < q; ++i) {
        cin >> newColonies[i].name >> newColonies[i].x >> newColonies[i].y;
    }
}

//Complejidad O(E * log(E) + V * log(V)), donde E es el numro de aristas y V es el numero de vertices
int kruskal(vector<Edge>& edges, vector<Edge>& newCabling, vector<string>& result) {
    UnionFind uf;

    // Inicializar conjuntos para todos los nodos
    for (const auto& edge : edges) {
        uf.makeSet(edge.from);
        uf.makeSet(edge.to);
    }

    // Unir las conexiones existentes
    for (const auto& cable : newCabling) {
        uf.unite(cable.from, cable.to);
    }

    // Eliminar las conexiones existentes del vector edges
    vector<Edge> filteredEdges;
    set<pair<string, string>> existingConnections;
    for (const auto& cable : newCabling) {
        existingConnections.insert({cable.from, cable.to});
        existingConnections.insert({cable.to, cable.from}); // Bidireccional
    }

    for (const auto& edge : edges) {
        if (existingConnections.count({edge.from, edge.to}) == 0) {
            filteredEdges.push_back(edge);
        } else {
            cout << "Omitir conexión existente: " << edge.from << " - " << edge.to << "\n";
        }
    }

    // Ordenar las aristas filtradas por costo
    sort(filteredEdges.begin(), filteredEdges.end(), [](const Edge& a, const Edge& b) {
        return a.cost < b.cost;
    });

    int totalCost = 0;

    for (const auto& edge : filteredEdges) {

        string rootFrom = uf.find(edge.from);
        string rootTo = uf.find(edge.to);


        if (rootFrom != rootTo) {
            uf.unite(edge.from, edge.to);

            result.push_back(edge.from + " - " + edge.to + " (" + to_string(edge.cost) + ")");
            totalCost += edge.cost;

        } else {
            cout << "Conexion descartada por formar un ciclo: " << edge.from << " - " << edge.to << "\n";
        }
    }

    cout << "Costo total del MST: " << totalCost << "\n";
    return totalCost;
}

// TSP para las colonias no centrales 
// Complejidad: O(n! * n), donde n es el numero de colonias no centrales (permuta todas las rutas posibles) no optimo xd 
pair<int, vector<string>> tspNonCentralsWithShortestPaths(
    const vector<Colony>& colonies,
    const unordered_map<string, unordered_map<string, int>>& shortestPaths) {

    // Filtrar colonias no centrales
    vector<string> nonCentrals;
    for (const auto& colony : colonies) {
        if (!colony.isCentral) {
            nonCentrals.push_back(colony.name);
        }
    }

    cout << "Colonias no centrales:\n";
    for (const auto& name : nonCentrals) {
        cout << name << " ";
    }
    cout << "\n";

    int n = nonCentrals.size();
    vector<string> bestPath;
    int minCost = numeric_limits<int>::max();

    // Generar todas las permutaciones posibles de las colonias no centrales
    sort(nonCentrals.begin(), nonCentrals.end());
    do {
        int currentCost = 0;
        bool valid = true;
        cout << "Probando ruta: ";
        for (const auto& name : nonCentrals) {
            cout << name << " ";
        }
        cout << "\n";

        for (int i = 0; i < n; ++i) {
            string from = nonCentrals[i];
            string to = nonCentrals[(i + 1) % n]; // Cerrar el ciclo
            if (shortestPaths.at(from).count(to) == 0 || shortestPaths.at(from).at(to) == numeric_limits<int>::max()) {
                valid = false;
                cout << "Conexion faltante: " << from << " -> " << to << "\n";
                break;
            }
            currentCost += shortestPaths.at(from).at(to);
        }

        if (valid) {
            cout << "Costo de la ruta: " << currentCost << "\n";
        } else {
            cout << "Ruta inválida\n";
        }

        if (valid && currentCost < minCost) {
            minCost = currentCost;
            bestPath = nonCentrals;
        }
    } while (next_permutation(nonCentrals.begin(), nonCentrals.end()));

    // Agregar el inicio al final para cerrar el ciclo
    bestPath.push_back(bestPath.front());

    cout << "Mejor ruta encontrada: ";
    for (const auto& name : bestPath) {
        cout << name << " ";
    }
    cout << "\nCosto total: " << minCost << "\n";

    return {minCost, bestPath};
}

// Floyd-Warshall para caminos más cortos entre todas las colonias
// Complejidad: O(V^3) donde V es el nimero de colonias
unordered_map<string, unordered_map<string, int>> floydWarshall(const vector<Colony>& colonies, const vector<Edge>& edges) {
    // Inicializar la matriz de distancias
    unordered_map<string, unordered_map<string, int>> dist;
    for (const auto& colony : colonies) {
        for (const auto& otherColony : colonies) {
            if (colony.name == otherColony.name) {
                dist[colony.name][otherColony.name] = 0;
            } else {
                dist[colony.name][otherColony.name] = numeric_limits<int>::max();
            }
        }
    }

    // Rellenar las distancias iniciales con las conexiones directas
    for (const auto& edge : edges) {
        dist[edge.from][edge.to] = edge.cost;
        dist[edge.to][edge.from] = edge.cost;
    }

    // Aplicar Floyd-Warshall
    for (const auto& k : colonies) {
        for (const auto& i : colonies) {
            for (const auto& j : colonies) {
                if (dist[i.name][k.name] != numeric_limits<int>::max() &&
                    dist[k.name][j.name] != numeric_limits<int>::max()) {
                    dist[i.name][j.name] = min(dist[i.name][j.name],
                                               dist[i.name][k.name] + dist[k.name][j.name]);
                }
            }
        }
    }

    return dist;
}
// Camino mas corto entre las colonias centrales 
//Complejidad O(N^3) donde N es el numero de colonias 
vector<string> floydWarshallCentrals(const vector<Colony>& colonies, const vector<Edge>& edges) {
    unordered_map<string, unordered_map<string, int>> dist;
    unordered_map<string, unordered_map<string, string>> next;

    // Inicializar la matriz de distancias y los caminos
    for (const auto& colony : colonies) {
        for (const auto& otherColony : colonies) {
            if (colony.name == otherColony.name) {
                dist[colony.name][otherColony.name] = 0;
            } else {
                dist[colony.name][otherColony.name] = numeric_limits<int>::max();
            }
            next[colony.name][otherColony.name] = "";
        }
    }

    for (const auto& edge : edges) {
        dist[edge.from][edge.to] = edge.cost;
        dist[edge.to][edge.from] = edge.cost;
        next[edge.from][edge.to] = edge.to;
        next[edge.to][edge.from] = edge.from;
    }

    for (const auto& k : colonies) {
        for (const auto& i : colonies) {
            for (const auto& j : colonies) {
                if (dist[i.name][k.name] != numeric_limits<int>::max() &&
                    dist[k.name][j.name] != numeric_limits<int>::max() &&
                    dist[i.name][j.name] > dist[i.name][k.name] + dist[k.name][j.name]) {
                    dist[i.name][j.name] = dist[i.name][k.name] + dist[k.name][j.name];
                    next[i.name][j.name] = next[i.name][k.name];
                }
            }
        }
    }

    // Extraer las rutas directas entre centrales
    vector<string> centralRoutes;
    set<pair<string, string>> printedPairs; // Para evitar duplicados
    for (const auto& central : colonies) {
        if (central.isCentral) {
            for (const auto& otherCentral : colonies) {
                if (otherCentral.isCentral && central.name != otherCentral.name) {
                    if (dist[central.name][otherCentral.name] != numeric_limits<int>::max() &&
                        !printedPairs.count({otherCentral.name, central.name})) {
                        // Reconstruir el camino
                        string path = central.name;
                        string current = central.name;
                        while (current != otherCentral.name) {
                            current = next[current][otherCentral.name];
                            path += " - " + current;
                        }
                        path += " (" + to_string(dist[central.name][otherCentral.name]) + ")";
                        centralRoutes.push_back(path);
                        printedPairs.insert({central.name, otherCentral.name});
                    }
                }
            }
        }
    }

    return centralRoutes;
}

// Conectar nuevas colonias utilizando distancia euclidiana
//Complejidad de O(Q x N) donde Q es el numero de colonias nuevas y N es el numero de colonias existentes
vector<pair<string, string>> connectNewColonies(const vector<Colony>& colonies, const vector<Colony>& newColonies) {
    vector<pair<string, string>> connections;

    for (const auto& newColony : newColonies) {
        double minDistance = numeric_limits<double>::max();
        string closestColony;
        for (const auto& colony : colonies) {
            double distance = euclideanDistance(newColony.x, newColony.y, colony.x, colony.y);
            if (distance < minDistance) {
                minDistance = distance;
                closestColony = colony.name;
            }
        }
        connections.emplace_back(newColony.name, closestColony);
    }

    return connections;
}

int main() {
    vector<Colony> colonies;
    vector<Edge> edges, newCabling;
    vector<Colony> newColonies;

    // Leer el archivo de entrada
    readInput(colonies, edges, newCabling, newColonies);

    // 1. Cableado óptimo
    vector<string> kruskalResult;
    int totalCost = kruskal(edges, newCabling, kruskalResult);

   // Calcular distancias mínimas entre todas las colonias
    auto shortestPaths = floydWarshall(colonies, edges);

    // 2. Ruta más corta entre no centrales usando distancias mínimas
    auto tspResult = tspNonCentralsWithShortestPaths(colonies, shortestPaths);
    int tspCost = tspResult.first;
    vector<string> tspPath = tspResult.second;

    // 3. Caminos más cortos entre centrales
    auto centralRoutes = floydWarshallCentrals(colonies, edges);

    // 4. Conectar nuevas colonias
    auto newConnections = connectNewColonies(colonies, newColonies);

    // Escribir resultados
    ofstream outputFile("checking2.txt");

    // Cableado óptimo
    outputFile << "-------------------\n";
   outputFile << "1 - Cableado optimo de nueva conexion.\n";
    for (const auto& line : kruskalResult) {
        outputFile << line << "\n";
    }
    outputFile << "Costo Total: " << totalCost << "\n\n";

    // Ruta más corta
    outputFile << "-------------------\n";
    outputFile << "2 - La ruta optima.\n";
    for (size_t i = 0; i < tspPath.size(); ++i) {
        outputFile << tspPath[i];
        if (i != tspPath.size() - 1) outputFile << " - ";
    }
    outputFile << "\nLa Ruta optima tiene un costo total de: " << tspCost << "\n\n";

    // Caminos más cortos entre centrales
    outputFile << "-------------------\n";
    outputFile << "3 - Caminos mas cortos entre centrales.\n";
    for (const auto& route : centralRoutes) {
        outputFile << route << "\n";
    }
    outputFile << "\n";

    // Conexión de nuevas colonias
    outputFile << "-------------------\n";
    outputFile << "4 - Conexion de nuevas colonias.\n";
    for (const auto& connection : newConnections) {
        outputFile << connection.first << " debe conectarse con " << connection.second << "\n";
    }
    outputFile << "\n";
    outputFile << "-------------------\n";
    outputFile.close();
    cout << "Archivo de salida generado: checking2.txt\n";

    return 0;
}
