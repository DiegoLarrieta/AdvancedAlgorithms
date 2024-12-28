/*
Luis Diego Dominguez Larrieta
A01275640

6 2
6 =  number of elements in the array
2 = value of heaters
****************************************
*/

#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;


int organzize_house(int number , int value, vector<int>&description){
  vector<int>heaters;

  for(int i = 0; i <number ; i++){
    if(description[i] == 1){
      heaters.push_back(i);
    }
  }
  if(heaters.empty()){
    return -1;
  }
  int num_heaters = 0;
  int last_covered = -1;
  int i=0;

  while(last_covered < number-1){
    int best = last_covered;

    while(i<heaters.size() && heaters[i] <= last_covered + value){
      best = max(best,heaters[i] + value-1);
      i++;
    }
    if(best == last_covered){
      return -1;
    }
    last_covered = best;
    num_heaters++;
  }
  return num_heaters;


}

int main(){

  int number_elements;

  int value;


  cin>>number_elements>>value;

  vector<int>description(number_elements);

  

  for(int i = 0; i<number_elements;i++){
    cin>>description[i];
  }


  cout<<organzize_house(number_elements,value,description)<<endl;

  return 0;
}