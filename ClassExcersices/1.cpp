//Renglones

#include<iostream>
#include<vector>

using namespace std;

#define MAX 10

int solve(int datos[MAX][MAX],int n){
  for(int i = n-2; i>=0; i--){
    for(int j=0;j<=i;j++){
      datos [i][j] += max(datos[i+1][j],datos[i+1][j+1]);
    }
  }
  return datos[0][0];
}

void leerDatos(int datos[MAX][MAX], int n){

  for(int i = 0;  i<n; i++){
    for(int j = 0; j<= i ; j++){
      cin>> datos[i][j];
    }
  }
}

void print(int datos[MAX][MAX],int n){
  for (int i=0; i<n ; i++){
    for(int j = 0; j<=i;j++){

    }
  }
}

int main(){

  int t , n;

  int datos[MAX][MAX];

  cin>>t;

  for(int i = 0; i<t; i++){
    cin>>n;
    leerDatos(datos,n);

    cout<< solve(datos,n)<<endl;
  }


  return 0;
}