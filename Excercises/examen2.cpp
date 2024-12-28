//
// Matricula: Luis Diego Dominguez Larrieta   
// Nombre: A01275640
//
#include <iostream>
#include <vector>
#include <climits>
#define MAX 10
using namespace std;

struct edge{
  int from, to, time;
  edge(int a, int b, int t){
    from = a;
    to = b;
    time = t;
  }
};
struct comm{
  char query;
  int from, to;
  comm(char q, int a, int b){
    query = q;
    from = a;
    to = b;
  }
};

// Complejidad:
void ejecuta_comandos(int n, vector<edge> &edges, vector<comm> &commands,vector<int> &salida){

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
/*
Ejemplo de Entrada:
5 8
1 2 4
1 3 2
1 4 4
2 3 1
2 5 3
3 4 7
3 5 1
4 5 4
6
c 1 5
c 4 2
c 5 3
a 3 5
c 5 3
c 3 5
Ejemplo de Salida:
3
6
1
4
4
*/