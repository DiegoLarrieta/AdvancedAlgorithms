// The Closest Pair
// Autor: YO
// Matrícula: A00135997
#include <iostream>
#include <algorithm>
#include <vector>
#include <cfloat>
#include <cmath>
#include <iomanip>
using namespace std;
struct Point{
  float x, y;
  Point(){
    x = y = 0;
  }
  Point(float x, float y){
    this->x = x;
    this->y = y;
  }
};
//Comparador para Sort con respecto X
bool compareX(const Point &p1, const Point &p2){
  return (p1.x < p2.x);
}
// Comparador para Sort con respecto a y
bool compareY(const Point &p1, const Point &p2){
  return (p1.y < p2.y);
}
// Saca la distancia eucleriana entre 2 puntos
float dist(Point &p1, Point &p2){
  return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}
float bruteForce(vector<Point> &P, int ini, int fin){
  float min_aux = FLT_MAX;
  for (int i=ini; i<fin; i++){
    for (int j=i+1; j<=fin; j++){
      min_aux = min(min_aux, dist(P[i], P[j]));
    }
  }
  return min_aux;
}
float stripClosest(vector<Point> &strip, float dMenor){
  float minStrip = FLT_MAX;
  sort(strip.begin(), strip.end(), compareY);
  for (int i=0; i<strip.size()-1; i++){
    for (int j=i+1; j<strip.size()-1 && (strip[j].y - strip[i].y) <
      minStrip; j++){
      minStrip = min(minStrip, dist(strip[i], strip[j]));
    }
  }
  return minStrip;
}
float closest_Helper(vector<Point> &P, int ini, int fin){
  if (fin-ini < 3){
    return bruteForce(P, ini, fin);
  }
  int mid = (fin-ini)/2+ini;
  Point midPoint = P[mid];
  float dl = closest_Helper(P, ini, mid);
  float dr = closest_Helper(P, mid+1, fin);
  float dMenor = min(dl, dr);
  vector<Point> strip;
  for (int i=ini; i<=fin; i++){
    if (abs(P[i].x-midPoint.x) < dMenor){
      strip.push_back(P[i]);
    }
  }
  float ds = stripClosest(strip, dMenor);
  dMenor = min(dMenor, ds);
  return dMenor;
}
// Complejidad: O(n logn)
float closest(vector<Point> &P){
  sort(P.begin(), P.end(), compareX);
  return closest_Helper(P, 0, P.size()-1);
}
int main(){
  // n = Cantidad de puntos
  int n;
  float x, y;
  cin >> n;
  vector<Point> P(n);
  for (int i=0; i<n; i++){
    cin >> x >> y;
    P[i].x = x;
    P[i].y = y;
  }
  float d = closest(P);
  cout << setprecision(2) << fixed;
  cout << "La distancia menor es de: " << d << endl;
  return 0;
}
/*
5
5 10
2 30
1 15
10 2
20 5
*/
