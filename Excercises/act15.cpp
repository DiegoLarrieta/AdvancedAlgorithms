/*
Sample Input 
5
Sparko 5 10
Rocky 2 30
Prue 1 15
Nico 10 2
Nerea 20 5

Sample Output
Best friend in BeagleTown are : Prue & Sparko (6.40)

Luis Diego Dominguez Larrieta

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cfloat>
#include <cmath>
#include <iomanip>
using namespace std;

struct Point {
    float x, y;
    string name;  // Agregamos el nombre del beagle

    Point() {
        x = y = 0;
        name = "";
    }

    Point(float x, float y, string name) {
        this->x = x;
        this->y = y;
        this->name = name;
    }
};

// Comparador para Sort con respecto a X 
bool compareX(const Point &p1, const Point &p2) {
    return (p1.x < p2.x);
}

// Comparador para Sort con respecto a Y
bool compareY(const Point &p1, const Point &p2) {
    return (p1.y < p2.y);
}

// Saca la distancia euclideana entre 2 puntos Complejidad O(1)
float dist(Point &p1, Point &p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

//Complejidad O(N^2)
float bruteForce(vector<Point> &P, int ini, int fin, string &beagle1, string &beagle2) {
    float min_aux = FLT_MAX;
    for (int i = ini; i < fin; i++) {
        for (int j = i + 1; j <= fin; j++) {
            float d = dist(P[i], P[j]);
            if (d < min_aux) {
                min_aux = d;
                beagle1 = P[i].name;
                beagle2 = P[j].name;
            }
        }
    }
    return min_aux;
}

//Complejidad O(N^2)
float stripClosest(vector<Point> &strip, float dMenor) {
    float minStrip = FLT_MAX;
    sort(strip.begin(), strip.end(), compareY);
    for (int i = 0; i < strip.size() - 1; i++) {
        for (int j = i + 1; j < strip.size() - 1 && (strip[j].y - strip[i].y) < minStrip; j++) {
            minStrip = min(minStrip, dist(strip[i], strip[j]));
        }
    }
    return minStrip;
}

//Complejidad O(N LOG N)
float closest_Helper(vector<Point> &P, int ini, int fin, string &beagle1, string &beagle2) {
    if (fin - ini < 3) {
        return bruteForce(P, ini, fin, beagle1, beagle2);
    }
    int mid = (fin - ini) / 2 + ini;
    Point midPoint = P[mid];
    float dl = closest_Helper(P, ini, mid, beagle1, beagle2);
    float dr = closest_Helper(P, mid + 1, fin, beagle1, beagle2);
    float dMenor = min(dl, dr);
    vector<Point> strip;
    for (int i = ini; i <= fin; i++) {
        if (abs(P[i].x - midPoint.x) < dMenor) {
            strip.push_back(P[i]);
        }
    }
    float ds = stripClosest(strip, dMenor);
    dMenor = min(dMenor, ds);
    return dMenor;
}

//Complejidad O(N LOG N)
float closest(vector<Point> &P, string &beagle1, string &beagle2) {
    sort(P.begin(), P.end(), compareX);
    return closest_Helper(P, 0, P.size() - 1, beagle1, beagle2);
}

int main() {
    // n = Cantidad de puntos
    int n;
    cin >> n;
    vector<Point> P(n);
    string beagle1, beagle2;
    for (int i = 0; i < n; i++) {
        string name;
        float x, y;
        cin >> name >> x >> y;
        P[i] = Point(x, y, name);  // Guardamos el nombre junto con las coordenadas
    }

    float d = closest(P, beagle1, beagle2);

    // nombres estn en orden lexico
    if (beagle1 > beagle2) {
        swap(beagle1, beagle2);
    }

    cout << fixed << setprecision(2);
    cout << "Best friend in BeagleTown are : " << beagle1 << " & " << beagle2 
         << " (" << d << ")" << endl;

    return 0;
}
