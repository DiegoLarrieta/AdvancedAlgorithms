// MST ( PRIM Y KRUSKAL)
//Luis Diego Dominguez Larrieta 
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <climits>
using namespace std;

struct Graph{

    int V, E, costMSTPrim, costMSTKruskal;
    vector<pair<int, pair<int, int>>> edges;        // Utiliza Kruskal;
    vector<vector< pair<int, int>>> adjList;        // Utiliza Prim
    vector<pair<int, int>> selectedEdgesK;          //Arcos seleccionados por Kruskal
    vector<pair<int, int>> selectedEdgesP;          //Arcos seleccionados por Prim
    Graph(int V, int E){
        this->V = V;
        this->E = E;
        adjList.resize(V);
        costMSTKruskal = costMSTPrim = 0;
    }

    //u = salida del arco
    //v = llegada del arco
    //w = Costo del arco
    void addEdge(int u, int v, int w){
        edges.push_back({w, {u,v}});        //First = costo, second = conexion
        adjList[u].push_back({v,w});
    }

    void load();
    void print();
    void primMST();
    void kruskalMST();
    void printEdgesP();
    void printEdgesK();

};


//Disjoint Set (Union-find)
struct DisjointSets{
    int *parent, *rank;
    int n;
    DisjointSets(int n ){
        this->n = n;
        parent = new int[n+1];
        rank = new int[n - 1];
        for(int i = 0; i <= n; i++){
            parent[i] = i;
            rank[i] = 0;
        }

    }
    int find(int u);                            //Encontrar el parent de 'u'
    void merge(int u, int v);           //Union de dos conjuntos dependiendo del rank


};



int DisjointSets::find(int u){
    if(u != parent[u]){
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void DisjointSets::merge(int u, int v){

    u = find(u);
    v = find(v);


    if(rank[u] > rank[v]){
        parent[v] = u;
    }
    else{
        parent[u] = v;
    }
    if(rank[u] == rank[v]){
        rank[v]++;
    }
}

void Graph::load(){
    int a, b, c;
    for(int i = 0; i < E; i++){
        cin >> a >> b >> c;
        addEdge(a, b, c);
        addEdge(b, a, c);
    }

}

void Graph::print(){
    cout << "Adjacent List: " << endl;
    for(int i = 0; i < V; i++){
        cout << i << ": ";
        for(int j = 0; j < adjList[i].size(); j++){
            cout << "(" << adjList[i][j].first << ", " << adjList[i][j].second << ") ";
        }
        cout << endl;
    }
}

void Graph::printEdgesP(){
    cout << "Selected Edges Prim: ";
    for(auto it:selectedEdgesP){
        cout << "(" << it.first << ", " << it.second << ") ";
    }
    cout << endl;
}

void  Graph::primMST(){

    int selSource = 0;
    costMSTPrim = 0;
    unordered_set<int> selected;            //Conjunto de vertices seleccionados
    unordered_set<int> missing;             //Cinjunto de vertices faltantes
    selected.insert(0);
    for(int i = 1; i < V; i++){
        missing.insert(i);
    }

    int connected = V - 1, minCost, selVertex;

    while(connected){
        minCost = INT_MAX;
        for(auto it1:selected){                                                                                       //checa los seleccionados
            for(auto it2:adjList[it1]){                                                               //checa las adjacencia de los seleccionados
                if(missing.find(it2.first) != missing.end() && it2.second < minCost){   //Encontrar si el elemento a analizar esta faltante y si su valor es menor al costo minimo
                    minCost = it2.second;
                    selVertex = it2.first;
                    selSource = it1;
                }
            }
        }

        costMSTPrim += minCost;
        selected.insert(selVertex);
        missing.erase(selVertex);
        selectedEdgesP.push_back({selSource, selVertex});
        connected--;

    }


}

//Complejidad: O(E log E)
void  Graph::kruskalMST(){
    sort(edges.begin(), edges.end());       //Ordenar los arcos en forma ascendente dle costo
    DisjointSets ds(V);
    costMSTKruskal = 0;
    for(auto it:edges){
        //cada casilla con {w,{u,v}}
        int p1 = ds.find(it.second.first);
        int p2 = ds.find(it.second.second);

        if(p1 != p2){
            costMSTKruskal += it.first;
            selectedEdgesK.push_back(it.second);
            ds.merge(it.second.first, it.second.second);
        }

    }
}

void Graph::printEdgesK(){
    cout << "Selected Edges Kruskal: ";
    for(auto it:selectedEdgesK){
        cout << "(" << it.first << ", " << it.second << ") ";
    }
    cout << endl;
}


int main()
{
    //V = cantidad de nodos(vertex)
    //E = cantidad de arcos(Edges)
    int V, E;
    cin >> V >> E;
    Graph g(V,E);

    g.load();
    //g.print();
    g.primMST();

    cout << "El costo total de MST por Prim es: " << g.costMSTPrim << endl;
    g.printEdgesP();

    g.kruskalMST();
    cout << "El costo total de MST por kruskal es: " << g.costMSTKruskal << endl;
    g.printEdgesK();



    //cout << "Hello world!" << endl;
    return 0;
}

/*
9 14

0 1 4

0 7 8

1 2 8

1 7 11

2 3 7

2 8 2

2 5 4

3 4 9

3 5 14

4 5 10

5 6 2

6 7 1

6 8 6

7 8 7

*/