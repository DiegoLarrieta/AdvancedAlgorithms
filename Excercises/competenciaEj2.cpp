/*
Luis Diego Dominguez Larrieta 
A01275640
*/

#include<iostream>
#include <climits>
#include <vector>

using namespace std;

int calculateRoute(int n,int t, const vector<pair<int, int>>& buses){
  int min_time = INT_MAX;
  int best_route = -1;

  for(int i = 0 ; i<n;i++){
    int s = buses[i].first;
    int d = buses[i].second;

    int next_bus_time;

    if(s>=t){
      next_bus_time = s;
    }else{
      if((t - s)%d == 0){
        next_bus_time = t;
      }else{
        next_bus_time = s + ((t - s + d -1)/d)*d;
      }
    }

    if(next_bus_time < min_time){
      min_time = next_bus_time;
      best_route = i+1;
    }
  }

  return best_route;

}


int main(){

  int n,t;

  cin>>n>>t;

  vector<pair<int, int>> buses(n);

     // Ingresamos los datos de los buses
    for (int i = 0; i < n; i++) {
        cin >> buses[i].first >> buses[i].second;
    }
    

  int result = calculateRoute(n,t,buses);

  cout<<result <<endl;


  return 0;
}