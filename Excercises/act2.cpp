//Luis Diego Dominguez Larrieta
//A01275640
/*
Este codigo contamos todo el numero de ceros y unos en la cadena binaria 
Por lo que el algoritmo recorre toda la cadena de longuitud N 
lo que significa que la complejidad es O(N)
*/
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// 4
//1100

int main (){

  int number;
  string s;

  cout << "Ingresa un numero en decimal: ";
  cin>> number;

  cout << "Ingresa un numero en binario: ";
  cin>> s;

  int contCero = count(s.begin(),s.end(),'0');
  int contOne =  count (s.begin(), s.end(),'1');
  
  int lenght = abs(contCero - contOne);

  cout<<lenght<< endl;
  return 0;
  }