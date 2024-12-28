#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

/*
1.Inicializar una matriz con la cantidad de objetos +1 de renglones y si es peso de la 
mochila + 1 de columnas 

2. Para i desde 0 hasta la cantidad de objetos

3.Para j desde 0 hasra el peso de la mochila{

4. Para i desde 1 hasta el peso de la mochila

5. ¿ ES EL PESO DE I MAJOR QUE J?

Si asigna a la matriz en la posicion [i][j], lo que tiene la matriz en la posicion p 2600
No asigna a la matriz en la posiicon [i][l], el mazimo 
}
*/

using namespace std;

#deine MAXOBJ 11
#dedine MAXMOCH 101

struct obj{
  int valor , peso;

  float valpeso;
}

bool my_comp(const obj &a, const obj &b){
  return a.valpeso > b.valpeso;
}

struct node{
  int niv, va , pa , vp;
  node(int niv, int va, int pa, int vp){
    this -> niv = niv;
    this -> va = va;
    this -> pa = pa;
    this -> vp = vp
  }
  bool operator<(const node &otro)const{

  }
};


int mochDP (vector<obj> &datos, int N, int PESO, int &contDP){
  int mat [MAXOBJ][MAXMOCH] = {0};
  for (int i = 1; i<N; i++){
    for(int j = 1;j <=peso;j++){
      if(datos[i-1].peso>j){
        mat[i][j] = mat[i-1][j];
      }else{
        
      }
    }
  }
}
int mochDyV(vector <obj> &datos , int N , INT peso , INT &contDyV){
  if (N==0){
    return 0;
  }
  contDyV++;
  if (PESO < datos [N-1].peso){
    return mochDyV(datos, N-1,PESO, contDyV);
  }else{
    return max(mochDyV(datos,N-1,PESO,contDyV),
      datos[N-1].valor + mochDyV(datos, N-1,PESO - datos[N-1].peso, contDyV));
  }
}

int calculaVP(vector <obj> &datos , int i , int vpAux, int ppesoAux, int PESO){
  int k = i + 1;
  while(k<N && pesoAux + datos[k].peso <= PESO){
    vpAux += datos[k].valor;
    pesoAux += datos[k].peso;
    k++;
  }
  if(k<N){
    vpAux += ((PESO = pesoAux) * datos[k].valpeso);
  }
  return vpAux;
}

void bt_Helper(vector<obj>&datos , int i  , int va, int pa , int vp, int N , int PESO ,int &valOptimo , int &contBT){
  contBT ++;
  if(i < N && pa<= PESO , && vp> valOptimo){
    if (va> valOptimo){
      valOptimo = va;
    }
    if(i + 1 < N){
      bt_Helper(datos, i +1 , va+ datos [i+1].valor, pa + datos[i+1].peso, vp,N,PESO,valOptimo , contBT);
      int vpAux = calculaVP(datos , i+1 , va , pa ,N, PESO);
      bt_Helper(datos, i+1, va , pa ,vpAux, N,PESO, valOptimo,contBT);
    }
  }
}

int mochilaBT(vector<obj> &datos, int N  int PESO , int &contBT){
  int valOptimo = 0;
  int vpAux = calculaVP(datos , -1, 0,0,N,PESO);
  bt_Helper(datos, -1 , 0,0,vpAux,N,PESO,valOptimo, contBT);
  return valOptimo;
}

int mochilaBB(vector<obj>&datos, int N , int PESO, int &contBB){
  priority_queue<node> pq;
  int valOptimo = 0;
  int vp = calculaVP(datos , -1,0,0,N,PESO);
  node arranque(-1, 0,0,vp);
  contBB++;

  pq.push(arranque);
  while(!pq.empty()){
    arranque = pq.top();
    pq.pop;
    if(arranque.vp > valOptimo){
      arranque.niv++;
      if(arranque.niv <N){
        contBB += 2;

        arranque.vp = calculateVP(datos, arranque.niv, arranque.val, arranque.pa , N, PESO){
          if(arranque.vp > valOptimo && arranque.pa <= PESO){
            pq.push(arranque);
          }
          arranque.va += datos[arranque.niv].valor;
          arranque.pa += datos[arranque.niv].peso;
          arranque.vp += calculaVP(datos, arranque.niv, arranque.va, arranque.pa, N,PESO){
            if(arranque.vp > valOptimo && arranque.pa <= PESO){
              pq.push(arranque);
            }
          }
        }
      }
    }
  }
}

int main(){

  int v , p , PESO;

  int contDyV=0, contDP=0, contBT=0, contBB=0;
  float vp;

  cin>>N::PESO;

  vector{obj}datos(N);

  float (int i = 0 ; i <n ; i**){
     cin>> v >> p;

     datos[i].valor  = v;
     datos[i].peso = p;
     datos[i].valpeso = vp;
  }
  cout<<"-------------"<<endl;
  cout<<"La mochila con DyV es :  "<<mochDyV(datos, N , PESO , contDyV);

  cout>>"con : "<<contBT<<" nodos"<<endl;

  cout<<"La mochila con DP es: "<<
};

void 
/*
4 16
10 5
40 2
50 10
30 5

3 30
50 5
60 10
140 20

6 89
64 26
85 22
52 4
99 18
39 13
54 9

*/