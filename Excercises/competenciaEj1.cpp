/*
Luis Diego Dominguez Larrieta 
A01275640
*/

#include <iostream>
using namespace std;

string grapesDistribution(int x, int y, int z, int green, int purple, int black) {
   
    if (green < x) return "NO";
    green -= x;

    int availableForDmitry = green + purple; 
    if (availableForDmitry < y) return "NO";

    int availableForMichael = availableForDmitry + black;  
    if (availableForMichael < z) return "NO"; 

    return "YES";
}

int main() {
    int x, y, z;  
    int green, purple, black;  

    // Leer la entrada
    cin >> x >> y >> z;
    cin >> green >> purple >> black;


    cout << grapesDistribution(x, y, z, green, purple, black) << endl;

    return 0;
}
