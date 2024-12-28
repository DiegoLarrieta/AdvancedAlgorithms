/*
Luis Diego Dominguez Larrieta 
A01275640
*/

#include<iostream>
#include<vector>

using namespace std;
string sub_array(int quantity , vector<int>numbers){
  int max_len = 1;  // La longitud máxima encontrada
  int current_len = 1;  // La longitud actual del subarray creciente

  for(int i = 0; i < quantity-1; i++){
    if(numbers[i] < numbers[i+1]){
      current_len++;
    }else{
      if(current_len > max_len){
        max_len = current_len;
      }
      current_len = 1;
    }
  }
  if(current_len > max_len){
    max_len = current_len;
  }

  return to_string(max_len);

}

int main(){

  int quantity;

  cin>>quantity;

  vector<int>numbers(quantity);
  

  for(int i = 0; i<quantity;i++){
    cin>>numbers[i];
  }

  string result = sub_array(quantity,numbers);

  cout<<result<<endl;

  return 0;
}