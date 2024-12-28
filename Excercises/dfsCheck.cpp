/*
This is the easy version of the problem. In this version , the given tree is a perfect binary tree and the constraints of n and q are lower, You can make hacks only if both versions of the problem are solved

You are given a perfect binaty tree consisting of n vertices, The vertices are numbered from 1 to n, and the root is the vertex 1, You are also given a permutation p1,p2...,pn of[1,2,...n]

Ypu need to answer q queries .For each query, you are given two integers x,y you need to swap px and py and determine if p1,p2,...pn is a valid DFS order of the given tree

Please note that the swaps are persistent throught queries

A perfect binaty tree is a tree with vertex 1 as its root, with size n = 2^k - 1 for a positive integer k, and where the parent of each vertex i (1<i<n) is [i/2].Thus , all leaves of this tree are at a distance k-1 from the root
A DFS order is found by calling the following dfs function on the given tree

dfs_order = []

function dfs(v):
    append v to the back of dfs_order
    pick an arbitrary permutation s of children of v
    for child in s:
        dfs(child)
dfs(1)

Note that the DFS order is not unique 

Each test contains multiple test cases. The first line contains the number of test cases t(1<t<10^4)
The description of the test cases follows 

The first line of each test case contains two integers n,q(3<n<65535,2<q<5*10^4) -> the number of vertices in the tree and the number of queries.It is guaranteed that n = 2^k-1 for a positive integer k

The next line contains n - 1 integers a2,a3,...,an(1<ai<i) -> the parent of each vertex in the given tree. It is guaranteed that ai = i/2

The next line contains n integers p1,p2,...,pn(1<pi<n), all the p, are distinct -> the initial permutation p

The next q lines each contain two integers x , y (1<x,y<n,x ! y) -> the positions of the elements to swap in the permutation

It is guaranteed that the sum of all n does not exceed 65535, and the sum of all 1 does not exceed 5*10^4


Output 
For each test case print q lines corresponding to the q queries. For each quuery, output YES i fthere is a DFS order that exactly equals the current permutation and output NO otherwise


Example
Input
2
3 3
1 1
1 2 3
2 3
3 2
1 3
7 4
1 1 2 2 3 3
1 2 3 4 5 6 7
3 5
2 5
3 7
4 6

Output
YES
YES
NO
YES
NO
NO
YES

Note 
In the first test case , the permutation p1,p2...,pn after each modification is [1,3,2],[1,2,3],[3,2,1],respectively . The first two permutations are valid DFS orders, the third is not a DFS order

In the second case, the permutation p1,p2,...pn after each modification is [1,2,5,4,3,6,7],[1,3,5,4,2,6,7],[1,3,7,4,2,6,5],[1,3,7,6,2,4,5], respectively


*/

#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

// Función para verificar si la permutación es un recorrido DFS válido
bool is_valid_dfs(const vector<int>& perm, const vector<int>& parent) {
    int n = perm.size();
    vector<int> pos(n + 1);

    // Guardar las posiciones actuales de cada nodo en la permutación
    for (int i = 0; i < n; i++) {
        pos[perm[i]] = i;  // pos[node] -> posición de node en la permutación
    }

    // Verificar que para cada nodo su padre esté antes en la permutación
    for (int i = 1; i < n; i++) {
        if (pos[parent[i]] > pos[i + 1]) {
            return false;
        }
    }
    return true;
}

// Función para procesar los casos de prueba
void solve() {
    int t;
    cin >> t; // Leer el número de casos de prueba

    while (t--) {
        int n, q;
        cin >> n >> q; // Leer n (número de nodos) y q (número de consultas)

        vector<int> parent(n);
        parent[0] = 0; // El nodo 1 (índice 0) es la raíz y no tiene padre

        // Leer los padres de los nodos (empezando desde el nodo 2)
        for (int i = 1; i < n; i++) {
            cin >> parent[i];
        }

        vector<int> perm(n);

        // Leer la permutación inicial
        for (int i = 0; i < n; i++) {
            cin >> perm[i];
        }

        // Procesar cada consulta
        for (int i = 0; i < q; i++) {
            int x, y;
            cin >> x >> y;

            // Ajustar a índices base-0
            x--; 
            y--;

            // Realizar el intercambio en la permutación
            swap(perm[x], perm[y]);

            // Verificar si la permutación actual es un recorrido DFS válido
            if (is_valid_dfs(perm, parent)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}


