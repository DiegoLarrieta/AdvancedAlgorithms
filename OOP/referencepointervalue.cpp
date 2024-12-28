#include <iostream>
#include <vector>

using namespace std;


//Pass By Value

void workValue(int x){
  x++;
  cout<<"Passed by Value "<<x<<endl;
};

//Pass By Reference 

void workReference(int &x){
  x++;
  cout<<"Passed by Reference "<<x<<endl;

}
//Pass By Pointer

void workPointer(int *x){
  *x++;
  cout<<"Passed by Pointer : " << *x<<endl;
}

int main(){
  int a = 10;
  int b =10;

  int c = 10;
  int *pC = &c;
  workValue(a);
  workReference(b);
  workPointer(pC);
  cout<<"Value : "<<a<<endl;
  cout<<"Reference : "<<b<<endl;
  cout<<"Pointer: "<<*pC<<endl;
  return 0;
}