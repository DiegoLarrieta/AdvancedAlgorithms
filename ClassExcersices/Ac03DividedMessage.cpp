#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*


Luis Diego Dominguez Larrieta 

A01275640

Ejemplo Input 1
aybabtu

Output
Left : ay
Middle bab
Right: tu

Ejemplo Input 2
nico

Output
Left:NO LEFT PART
Middle:n
Right: ico

En este caso como no hay ningun palindromo toma el primer caracter como middle, que representa el palindormo mas largo

Ejemplo Input 3
bab

Output 
Left: NO LEFT PART
Middle : bab
Right: NO RIGHT PART

Complejidad de Algoritmo O(N)

*/

// Función para preprocesar la cadena, añadiendo separadores entre caracteres
string preprocesar(const string& s) {
    if (s.empty()) return "^$";  // Caso especial para cadena vacía
    string ret = "^";  // Agregamos un delimitador inicial
    for (char c : s) {
        ret += "#" + string(1, c);
    }
    ret += "#$";  // Delimitador final
    return ret;
}

// Función que implementa el algoritmo de Manacher
string palindromoMasLargo(const string& s, int &start, int &len) {
    string T = preprocesar(s);  // Preprocesamos la cadena original
    int n = T.length();
    vector<int> P(n, 0);  // Arreglo para almacenar el radio de los palíndromos
    int C = 0, R = 0;  // C es el centro actual, R es el borde derecho actual

    // Algoritmo principal
    for (int i = 1; i < n - 1; ++i) {
        int i_mirror = 2 * C - i;  // Índice simétrico con respecto a C

        if (R > i) {
            P[i] = min(R - i, P[i_mirror]);  // Limitamos el radio si excede R
        }

        // Intentamos expandir el palíndromo centrado en i
        while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
            P[i]++;
        }

        // Si el palíndromo centrado en i se expande más allá de R, actualizamos C y R
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }

    // Encontramos el palíndromo más largo
    int maxLen = 0;
    int centerIndex = 0;
    for (int i = 1; i < n - 1; ++i) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }

    // Extraemos el palíndromo de la cadena original
    start = (centerIndex - maxLen) / 2;  // Convertimos el índice de la cadena preprocesada a la original
    len = maxLen;
    return s.substr(start, maxLen);  // Extraemos el palíndromo más largo
}

int main() {

    string s; //= "aybabtu";
    cin>>s;

    int start = 0;
    int len = 0;

    string longestP = palindromoMasLargo(s,start,len);

    string left = start == 0 ? "NO LEFT PART" : s.substr(0,start);
    string right = (start + len >= s.length()) ? "NO RIGHT PART" : s.substr(start + len);

    cout<<"Left: "<<left<<endl;

    cout << "Middle: " << longestP << endl;

    cout<<"Right: "<<right<<endl;

    return 0;
}
