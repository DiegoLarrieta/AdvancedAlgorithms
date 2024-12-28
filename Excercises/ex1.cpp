#include <iostream>
using namespace std;
#include <vector>

int cuantos(vector<int> v ){
  int cont = 0;
  for(int i = 0; i<v.size();i++){
    if(v[i] > 100){
      cont ++;
    }
  }
  return cont;
}

int cuantos2(vector<int> v){
  return cuantosDivV(v,v.size()-1);
}

int cuantosDivV(vector<int> v , int ini , int fin){
  if(ini == fin){
    return (v[ini]>100 ? 1 : 0);
  }
  int mit == (int + fin)/2;
  return cuantosDivV(v, ini, fin );
}

int main(){

  vector<int> arr = { 100, 11, 13, 5, 6, 7 };
  cuantos(arr);

  return 0;
}
