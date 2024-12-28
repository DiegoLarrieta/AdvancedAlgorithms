//Algoritmo de backtracking 

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//Complejidad 0(2^n)

void sum_of_subset(int i , int acum, int total, int n, int VALOR, vector<int> &obj, vector<bool> &include){
  if(acum + total >= VALOR && (acum == VALOR || acum + obj[i+1] <= VALOR )){
    if(acum == VALOR){
      for(int k = 0; k <n ; k++){
        if(include [k]){
          cout<<obj[k]<<"";
        }
      }
      cout<<endl;
    }
    else{
      include[i+1] = true; //Si incluyo el siguiente objeto
      sum_of_subset(i+1,acum+obj[i+1],total-obj[i+1],n,VALOR,obj,include);
      include[i+1] = false;
      sum_of_subset(i+1 , acum , total-obj[i+1],n,VALOR,obj,include);
    }
  }
}

int main(){

  int n, VALOR;

  vector<bool> include;

  vector<int> obj;

  cin>>n>>VALOR;

  int dato,total = 0;

  for(int i = 0; i<n;i++){
    cin>>dato;
    obj.push_back(dato);
    total += dato;
    include.push_back(false);

  }
  sort(obj.begin(),obj.end());
  sum_of_subset(-1,0,total,n,VALOR,obj,include);
  return 0;
}