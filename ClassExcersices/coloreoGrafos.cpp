// Algoritmo de Welsh Powell para coloreo de grafos
// Autor: Luis Diego Dominguez Larrieta 
// Matrícula: A01275640

/*
Inicialización de la matriz de adyacencia: O(n²)
Ordenamiento de los vértices por grado: O(n log n)
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;
#define MAX 100
struct color{
  int conex; // Cant de conexiones
  int vtx; // El número de vertice
};
// Comparador para ordenar ascendentemente, y cuando son iguales gane el vertice con índice menor
bool my_cmp(const color &c1, const color &c2){
//ayudame a terminar esto
  if(c1.conex == c2.conex){
    return c1.vtx < c2.vtx;
  }
  return c1.conex > c2.conex;
}
// Regresa true si nadie del conjunto conj tiene adjacencia con el vertice j, falso en caso contrario.
bool canColor(bool matAdj[MAX][MAX], unordered_set<int> &conj, int j){
// Tu código
      // Recorremos el conjunto de vértices ya coloreados
    for (int vertex : conj) {
        // Si existe una conexión en la matriz de adyacencia con algún vértice ya coloreado, no puede colorearse
        if (matAdj[vertex][j]) {
            return false;
        }
    }
    // Si no tiene conexión con ningún vértice del conjunto, puede colorearse
  return true;
}
// Lectura de arcos y generación de grado del vertice
void leeArcos(bool matAdj[MAX][MAX], vector<color> &vtxColor, int m){
  int u , v;
  for(int i = 0; i<m;i++){
    cin>>u>>v;
    matAdj[u-1][v-1] = matAdj[v-1][u-1] = true;

    vtxColor[u-1].conex++;
    vtxColor[v-1].conex++;
  }
}
vector<int> colorGraph(bool matAdj[MAX][MAX], vector<color> &vtxColor) {
    int numColor = 0; // Número de colores
    int n = vtxColor.size(); // Cantidad de vértices
    vector<int> colored(n, 0); // Vector que almacena el color de cada vértice (inicializado en 0)

    // Recorremos todos los vértices ordenados por grado (vtxColor ya está ordenado)
    for (int a = 0; a < n; a++) {
        int i = vtxColor[a].vtx; // Obtener el índice del vértice

        // Si el vértice aún no tiene color
        if (!colored[i]) {
            numColor++; // Incrementar el número de colores
            colored[i] = numColor; // Asignar el nuevo color al vértice
            unordered_set<int> conj; // Conjunto de vértices coloreados con el color actual
            conj.insert(i); // Insertar el vértice actual en el conjunto

            // Intentamos colorear los vértices restantes con el mismo color
            for (int b = a + 1; b < n; b++) {
                int j = vtxColor[b].vtx; // Obtener el índice del siguiente vértice

                // Si el vértice aún no tiene color y no tiene adyacencias con el conjunto actual de vértices
                if (!colored[j] && canColor(matAdj, conj, j)) {
                    colored[j] = numColor; // Asignar el mismo color al vértice
                    conj.insert(j); // Insertar este vértice en el conjunto de coloreados
                }
            }
        }
    }
    return colored; // Devolver el vector de colores
}
int main(){
// n = número de vertices
// m = número de arcos
  int n, m;
  cin >> n >> m;
  bool matAdj[MAX][MAX];
  for (int i=0; i<MAX; i++){
    for (int j=0; j<MAX; j++){
      matAdj[i][j] = false;
    }
  }
  // vector de grados de los vertices
  vector<color> vtxColor;
  color c;
  for (int i=0; i<n; i++){
  c.conex = 0;
  c.vtx = i;
  vtxColor.push_back(c);
  }
  leeArcos(matAdj, vtxColor, m);
  sort(vtxColor.begin(), vtxColor.end(), my_cmp);
  vector<int> colored = colorGraph(matAdj, vtxColor);
  for (int i=0; i<n; i++){
    cout << "Vertex " << (i+1) << " with color " << colored[i] << endl;
  }
  return 0;
}
/*
7 11
1 2
1 3
1 4
2 3
2 5
3 4
3 5
4 5
4 6
5 7
6 7
*/
