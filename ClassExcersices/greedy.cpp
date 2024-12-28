#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Complejidad O(n)
vector<int> leeDatos(int n ){
  vector<int> datos(n);
  for(int i =0; i<n;i++){
    cin>>datos[i];
  }
  return datos;
}

int solve(vector<int>&datos){
  int salida = 0;
  //Ordenar ascendentemente 
  //sort(datos.begin(),datos.end());
  //ordenar descendentemente 

  sort(datos.begin(),datos.end(),greater<int>());
  for(int i = 0; i<datos.size();i++){
    salida *= 10;
    salida += datos[i];
  }
  return datos;
}

int main(){
  int n;
  cin>>n;

  vector<int> datos =  


}