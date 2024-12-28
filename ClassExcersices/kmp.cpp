/*
Luis Diego Dominguez Larrieta 
A01275640
*/
#include <iostream>
#include <vector>

using namespace std;
/*
input 

ababacbabaadaba
aba

new output
cbad

*/

//Complejidad O(m) 

vector<int> lps(string p){
  int n=p.size();
  vector<int>lpsv(n,0);
  int j = 0, i= 1;
  while( i < n){
    if(p[i] == p[j]){
      lpsv[i++] = ++j;
    }
    else{
      if(j==0){
        lpsv[i] = 0;
        i++;

      }
      else{
        j = lpsv[j-1];
      }
    }
  }
  return lpsv;
}
//Complejidad 0(n)

vector<int> kmp(string texto, string patron){
    vector<int> posMatch;
    vector<int> lpsv = lps(patron);
    int j  = 0, i = 0;
    int n = texto.length();
    int m = patron.length();
    while(i<n){
        if (texto[i] == patron[j]){
            i++;
            j++;
            if (j == m){
                posMatch.push_back(i-m);
                j = lpsv[j-1];
            }
        }
        else{
            if(j == 0){
                i++;
            }
            else{
                j = lpsv[j - 1];
            }
           
        }
    }
    return posMatch;
}


int main(){
  string texto, patron;

    // Solicitamos al usuario que ingrese el texto y el patrón
    cin >> texto;
    cin >> patron;

    // Llamamos a la función KMP para encontrar todas las posiciones del patrón
    vector<int> posMatch = kmp(texto, patron);
    int j = 0;
    bool coincidencia = false;
    
    if (posMatch.size() == 0){
        cout << texto << endl;
    }
    else{
      for (int i = 0; i < texto.size(); i++){ 
          if (i != posMatch[j]){
            cout << texto[i];
            coincidencia = true;
          }
          else if (i == posMatch[j]){
            if (i +  patron.length() - 1 == posMatch[j + 1]){
              j++;
              i = posMatch[j] - 1;
            }
            else{
              i += patron.length() - 1;
              j++;    
            }
            if (i ==  texto.size() - 1 && !coincidencia){
              cout << "NO TRUSTED MESSAGE" << endl;
            }    
          }
      }
            //Complejidad O(n)
        cout << endl;
        }
}