/*
Luis Diego Dominguez Larrieta 
A01275640
*/
#include<iostream>
#include<string>

using namespace std;

int main() {
    string jugadores; 
    cin >> jugadores;

    
    int seguidos = 1;
    bool peligroso = false;

    
    for (int i = 1; i < jugadores.length(); i++) {
        if (jugadores[i] == jugadores[i - 1]) {
            seguidos++; 
            if (seguidos >= 7) {
                peligroso = true; 
                break;
            }
        } else {
            seguidos = 1;
        }
    }

    if (peligroso) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
