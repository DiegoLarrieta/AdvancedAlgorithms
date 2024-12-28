/*
Matricula: A01275640
Nombre:Luis Diego Dominguez Larrieta 
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

// Complejidad: O(n) Se recorre el tamaño del vector una vez 

bool iguales(vector<int> &d, int k){
  // Aquí va tu código.
  unordered_map<int,int> indices; //Almacenar al vector y al vecino

  for(int i = 0 ; i<d.size();i++){
    if(indices.find(d[i]) != indices.end()){
      // si el valor esta en el mapa
      //revisamos la diferencia y verificamos con el valor de k 
      if(abs (i - indices[d[i]]) <= k ){
        return true;
      }
    }
    //Actualizar el indice del valor en el mapa 
    indices[d[i]] = i;
  }

      return false;
}
int main(){
  int n, k;
  cin >> n >> k;
  vector<int> datos(n);
  for (int i=0; i<n; i++){
    cin>>datos[i];
  }
  cout << (iguales(datos, k)? "YES" : "NO") <<endl;
}
/*
Ejemplo 1
4 3
1 2 3 1
Ejemplo 2
4 1
1 0 1 1
Ejmplo 3
6 2
1 2 3 1 2 3
*/
