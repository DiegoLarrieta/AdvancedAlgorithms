#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*
Luis Diego Dominguez Larrieta 
A01275640

Complejidad O(N*M) donde N es el numero de filas y M es el numero de columnas de la matriz
*/
int trayecto(const vector<vector<int>>&matrix, int filas, int columnas){
  vector<vector<int>> mapa(filas,vector<int>(columnas,0));

  mapa[0][0] = matrix[0][0];

  for(int i = 1 ; i<filas;i++){
    mapa[i][0] = mapa[i - 1][0] + matrix[i][0];
  }

  for(int j=1; j<columnas; j++){
    mapa[0][j] = mapa [0][j - 1] + matrix[0][j];
  }

  for(int i = 1; i<filas ; i++){
    for(int j=1; j<columnas; j++){
      mapa[i][j] = min(mapa[i-1][j] , mapa[i][j-1]) + matrix [i][j];
    }
  }

  return mapa[filas-1][columnas-1];



}

int main(){

  //Cantidad de filas 
  int filas, columnas;
  cin>>filas>>columnas;


  vector<vector<int>> matrix (filas,vector<int>(columnas));

  for(int i = 0 ; i<filas;i++){
    for(int j = 0 ; j<columnas;j++){
      cin>>matrix[i][j];
    }
  }

  int resultado = trayecto(matrix,filas,columnas);
  cout<<resultado<<endl;

  
  return 0;
}