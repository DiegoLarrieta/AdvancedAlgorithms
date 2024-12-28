/*
Luis Diego Dominguez Larrieta 
A01275640

El algoritmo de Knuth-Morris-Pratt (KMP) es un método eficiente para encontrar un patrón
dentro de un texto. Lo importante de este algoritmo es que aprovecha la información del patrón
para evitar comparaciones innecesarias.

KMP usa una técnica para evitar retrocesos innecesarios en el texto. Si ya has hecho algunas
comparaciones y encuentras un desajuste, no vuelves a comenzar desde el principio, sino que aprovechas
la información que ya has aprendido.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Función para construir el arreglo de fallos (pi o LPS: Longest Prefix Suffix)
void computeLPSArray(string pattern, vector<int>& lps) {
    int length = 0; // Longitud del prefijo más largo que es también sufijo
    lps[0] = 0; // El primer valor del LPS siempre es 0
    int i = 1;  // Empezamos en el segundo carácter del patrón

    // Bucle para calcular el LPS para cada posición del patrón
    while (i < pattern.length()) {
        if (pattern[i] == pattern[length]) {
            // Si hay coincidencia, incrementamos la longitud y almacenamos el valor en lps[i]
            length++;
            lps[i] = length;
            i++;
        } else {
            // Si no hay coincidencia
            if (length != 0) {
                // Retrocedemos al valor anterior del prefijo más largo
                length = lps[length - 1];
            } else {
                // Si la longitud es 0, simplemente asignamos 0 a lps[i] y avanzamos
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Función para realizar la búsqueda del patrón en el texto usando KMP
void KMPSearch(string pattern, string text) {
    int m = pattern.length();
    int n = text.length();

    // Arreglo para almacenar el LPS
    vector<int> lps(m);

    // Preprocesamos el patrón para llenar el arreglo de LPS
    computeLPSArray(pattern, lps);

    int i = 0; // Índice para el texto
    int j = 0; // Índice para el patrón

    // Empezamos a comparar el patrón con el texto
    while (i < n) {
        if (pattern[j] == text[i]) {
            // Si hay coincidencia, avanzamos ambos índices
            i++;
            j++;
        }

        if (j == m) {
            // Si encontramos todo el patrón en el texto
            cout << "Patrón encontrado en el índice " << i - j << endl;
            j = lps[j - 1]; // Usamos el LPS para continuar la búsqueda
        }
        else if (i < n && pattern[j] != text[i]) {
            // Si ocurre un desajuste después de j coincidencias
            if (j != 0) {
                // Retrocedemos j al valor de lps[j-1] para evitar comparaciones innecesarias
                j = lps[j - 1];
            } else {
                // Si j es 0, avanzamos el índice en el texto
                i++;
            }
        }
    }
}

// Función principal para probar el algoritmo KMP
int main() {
    string text = "ABABDABACDABABCABAB";   // Texto donde vamos a buscar
    string pattern = "ABABCABAB";          // Patrón que queremos encontrar

    // Llamamos a la función de búsqueda KMP
    KMPSearch(pattern, text);

    return 0;
}
