#include <iostream>
#include <climits>
#include <queue>

#define MAX 21
#define INF INT_MAX

using namespace std;
/*
Luis Diego Dominguez Larrieta 
*/

struct node{
    int nivel; // nivel en el que esta el nodo dentro del arco de búsqueda de soluciones
    int costoAcum; //Costo Acumulado del Nodo
    int costoPosible; //Costo posible
    int verticeAnterior; // Vertice Anterior de la trayectoria
    int verticeActual; // Vertice Actual de la trayectoria
    bool visitados[MAX] = {false}; //Saber si el nodo fue visitado o no
    bool operator<(const node &otro) const{
        return costoPosible >= otro.costoPosible;
    }
};

void calcularCostoPosible(node &nodoActual, int matAdj[MAX][MAX], int n){
    nodoActual.costoPosible = nodoActual.costoAcum;
    int costoObtenido;
    for(int i = 1; i <= n; i++){ 
        costoObtenido = INF;
        // El nodo i no ha sido visitado o es el ultimo en la trayectoria actual
        if(!nodoActual.visitados[i] || i == nodoActual.verticeActual){
            if (!nodoActual.visitados[i]){ //El nodo i no ha sido visitado
                for(int j = 1; j <= n; j++){
                    if(i != j && (!nodoActual.visitados[j] || j==1)){
                        costoObtenido = min(costoObtenido, matAdj[i][j]);
                    }
                }
            }
            else{ //El ultimo nodo de la trayectoria
                for(int j = 1; j <= n; j++){
                    if(!nodoActual.visitados[j]){
                        costoObtenido = min(costoObtenido, matAdj[i][j]);
                    }
                }
            }
        }
        if (costoObtenido != INF){
            nodoActual.costoPosible += costoObtenido; //Cambio del codigo original
        }
    }
}

int tsp(int matAdj[MAX][MAX], int n){
    int costoOptimo = INF;
    node raiz;
    raiz.nivel = 0;
    raiz.costoAcum = 0;
    raiz.verticeActual = 1;
    raiz.verticeAnterior = 0;
    raiz.visitados[1] = true;
    calcularCostoPosible(raiz,matAdj,n);
    priority_queue<node> pq;
    pq.push(raiz);
    while(!pq.empty()){
        raiz = pq.top();
        pq.pop();
        if(raiz.costoPosible < costoOptimo){
            for(int i = 1; i <= n; i++){
                if(!raiz.visitados[i] && matAdj[i][raiz.verticeActual] != INF){  
                    node aux = raiz;
                    aux.nivel++;
                    aux.verticeAnterior = raiz.verticeActual;
                    aux.costoAcum += matAdj[aux.verticeAnterior][i];
                    aux.verticeActual = i;
                    aux.visitados[i] = true;
                    if(aux.nivel == n - 1){ 
                        if(matAdj[aux.verticeActual][1] != INF){
                            aux.costoAcum += matAdj[aux.verticeActual][1];
                            if(aux.costoAcum < costoOptimo){
                                costoOptimo = aux.costoAcum;
                            }
                        }
                    }
                    else{
                        calcularCostoPosible(aux, matAdj, n);
                        pq.push(aux);
                    }
                }
            }
        }
    }
    return costoOptimo;
}

void iniciaMat(int matAdj[MAX][MAX]){
    for(int i = 0; i < MAX; i++){
        matAdj[i][i] = 0;
        for(int j = i+1; j < MAX; j++){
            matAdj[i][j] = matAdj[j][i] = INF;
        }
    }
}

void leerArcos(int matAdj[MAX][MAX], int m){
    char a, b;
    int c;
    for(int i = 0; i < m; i++){
        cin >> a >> b >> c;
        matAdj[a-'A'+1][b-'A'+1] = matAdj[b-'A'+1][a-'A'+1] = c;
    }
}

int main(){
    int n, m, resultado = 0;
    cin >> n >> m ; 
    int matAdj[MAX][MAX];
    iniciaMat(matAdj);
    leerArcos(matAdj, m);
    resultado = tsp(matAdj, n);
    cout << (resultado == INF ? "INF" : to_string(resultado)) << endl;
    return 0;
}