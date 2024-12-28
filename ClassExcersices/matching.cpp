#include <iostream>
#include <vector>
using namespace std;

vector<int> z_function (string texto){
  int n = texto.length();
  vector<int> z(n,0);

  for(int i = 1 , l= 0, r=0; i<n; i++){
    if(i<r){
      z[i] = min(r-i, z[i-l]);
    }
    while(i+z[i] < n && texto [z[i]] == texto[i+z[i]]){
      z[i]++;
    }
    if(i+z[i] > r){
      l = i;
      r = i +z[i];
    }
  }
  return z;

} 

int main(){

  string P, T;

  cin >> P>>T;

  string texto = P + "$" + T;
  vector<int> z = z_function(texto);
  bool flag = false;
  for(int i = P.size()+1; i<texto.size();i++){
    if(z[i] == P.size()){
      cout<< i-P.size()-1<<"";
      flag = true;
    }
  }
  if(!flag){
    cout<<"No hay coincidencias"<<endl;
  }
  cout<<endl;
  return 0;
}

