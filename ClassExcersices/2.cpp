/*
ACT en clase 2.
Hacer como un ejemplo de cabajo que se tiene mover en un tablero de ajedrez, 
de la esquina superior derecha a la inferior
*/
/*
Luis Diego Dominguez Larrieta
A01275640

Complejidad es O(N*M) donde N y M son las variables correspondientes a la fila y columna del tablero


*/
#include <iostream>
#include<vector>

using namespace std;

#define MAX 50


int solve(int tablero[MAX][MAX],int fila, int columna){
  for(int i = 0; i<fila; i++){
    for(int j  = 0 ; j< columna ; j++){
      if(i+2<fila && j+1<columna){
        tablero[i+2][j+1] += tablero[i][j];
      }
      if(i+1<fila && j+2<columna){
        tablero[i+1][j+2] += tablero[i][j];

      }
    }
  }
  return tablero[fila-1][columna-1];

}

void iniTablero(int tablero[MAX][MAX]){
  for(int i=0; i<MAX; i++){
    for(int j=0;j<MAX;j++){
      tablero [i][j] = 0;
    }
  }
  tablero[0][0] = 1;
}


int main(){
  int fila, columna;

  int tablero[MAX][MAX];

  iniTablero(tablero);

  cin>> fila, columna;

  cout<<solve(tablero,fila,columna)<<endl;
  

  return 0;
}