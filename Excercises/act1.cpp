//Luis Diego Dominguez Larrieta
//A01275640

/*
La complejidad del mapeo de todas las letras ya que son 26 toma O(26),
Lo que se vuelve en O(1), sin embargo como el bucle se hace N veces 
la complejidad es de O(n)

*/
/*
6
abacabadaba
a b
b c
a d
e g
f a
b b
Sample Output
cdcbcdcfcdc
.
.

*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n; // Leer número de diseñadores

    string nameProduct;
    cin >> nameProduct; // Leer nombre del producto

    vector<char> map(26);
    for(int i = 0; i < 26; i++) {
        map[i] = 'a' + i;
    }

    for(int i = 0; i < n; i++) {
        char x1, y1;
        cin >> x1 >> y1;

        // Realizar el cambio
        for(int j = 0; j < 26; j++) {
            if(map[j] == x1) {
                map[j] = y1;
            } else if(map[j] == y1) {
                map[j] = x1;
            }
        }
    }

    for(char &c : nameProduct) {
        c = map[c - 'a'];
    }

    cout << nameProduct << endl;

    return 0;
}
