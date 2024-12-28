/*
Luis Diego Dominguez Larrieta
A01275640
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Función para calcular el array de prefijos "lps" (Longest Prefix Suffix) para el algoritmo KMP
vector<int> calcularLPS(string patron) {
    int longitud = patron.size();
    vector<int> lpsArray(longitud, 0);
    int j = 0, i = 1;
    while (i < longitud) {
        if (patron[i] == patron[j]) {
            lpsArray[i++] = ++j;
        } else {
            if (j == 0) {
                lpsArray[i] = 0;
                i++;
            } else {
                j = lpsArray[j - 1];
            }
        }
    }
    return lpsArray;
}

// Implementación del algoritmo KMP para buscar un patrón en un texto
// Complejidad O(N)
vector<int> buscarKMP(string texto, string patron) {
    vector<int> posiciones;
    vector<int> lpsArray = calcularLPS(patron);
    int j = 0, i = 0;
    int longitudTexto = texto.length();
    int longitudPatron = patron.length();

    while (i < longitudTexto) {
        if (texto[i] == patron[j]) {
            i++;
            j++;
            if (j == longitudPatron) {
                posiciones.push_back(i - longitudPatron);
                j = 0;  // Reiniciar el patrón
            }
        } else {
            if (j == 0) {
                i++;
            } else {
                j = lpsArray[j - 1];
            }
        }
    }
    return posiciones;
}

// Algoritmo de Manacher para encontrar el palíndromo más largo en un texto
// Complejidad O(N)
vector<int> obtenerPalindromoMasLargo(const string& cadena) {
    vector<int> resultadoPalindromo(2);
    string transformada = "#";
    for (char c : cadena) {
        transformada += c;
        transformada += '#';
    }

    int n = transformada.size();
    vector<int> p(n, 0);
    int centro = 0, radio = 0;
    int longitudMaxima = 0;
    int indiceCentro = 0;

    for (int i = 0; i < n; ++i) {
        int espejo = 2 * centro - i;

        if (i < radio) {
            p[i] = min(radio - i, p[espejo]);
        }

        while (i + p[i] + 1 < n && i - p[i] - 1 >= 0 && transformada[i + p[i] + 1] == transformada[i - p[i] - 1]) {
            p[i]++;
        }

        if (i + p[i] > radio) {
            centro = i;
            radio = i + p[i];
        }

        if (p[i] > longitudMaxima) {
            longitudMaxima = p[i];
            indiceCentro = i;
        }
    }

    int inicio = (indiceCentro - longitudMaxima) / 2;
    resultadoPalindromo[0] = inicio;
    resultadoPalindromo[1] = longitudMaxima;
    return resultadoPalindromo;
}

// Algoritmo para encontrar el substring común más largo entre dos palabras (LCS)
// Complejidad O(N*M) DONDE SON LAS LONGITUDES DE CADA PALABRA
string obtenerLCS(string palabra1, string palabra2) {
    int n = palabra1.length();
    int m = palabra2.length();
    vector<vector<int>> tablaLongitud(n + 1, vector<int>(m + 1, 0));
    int maximoResultado = 0;
    int finResultado = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (palabra1[i - 1] == palabra2[j - 1]) {
                tablaLongitud[i][j] = tablaLongitud[i - 1][j - 1] + 1;
                if (tablaLongitud[i][j] > maximoResultado) {
                    maximoResultado = tablaLongitud[i][j];
                    finResultado = i;
                }
            } else {
                tablaLongitud[i][j] = 0;
            }
        }
    }
    return palabra1.substr(finResultado - maximoResultado, maximoResultado);
}

// Nueva versión de la función para generar subsecuencias eliminando dos caracteres en vez de uno
vector<string> generarSubsecuencias(const string& codigo) {
    vector<string> subsecuencias;
    int longitud = codigo.size();
    for (int i = 0; i < longitud; ++i) {
        for (int j = i + 1; j < longitud; ++j) {
            string subsecuencia = codigo.substr(0, i) + codigo.substr(i + 1, j - i - 1) + codigo.substr(j + 1);
            subsecuencias.push_back(subsecuencia);
        }
    }
    return subsecuencias;
}

// Función para contar la cantidad de veces que aparece una subsecuencia en un texto usando KMP
int contarCoincidencias(const string& texto, const string& subsecuencia) {
    vector<int> posicionesCoincidencias = buscarKMP(texto, subsecuencia);
    return posicionesCoincidencias.size();
}

int main() {
    vector<string> transmisiones;  // Almacenar cada archivo de transmisión
    vector<int> coincidencias;  // Almacenar las posiciones de los patrones en cada transmisión
    string subsecuenciaMasFrecuente;
    int maxCoincidencias = 0;
    string archivoMasFrecuente;  // Archivo con más coincidencias

    ifstream archivoCodigoMalicioso("mcode.txt");
    string archivos[] = {"Transmission1.txt", "Transmission2.txt", "Transmission3.txt"};

    // Leer cada archivo de transmisión
    for (int i = 0; i < 3; ++i) {
        ifstream archivoTransmision(archivos[i]);
        string lineaTransmision;
        while (getline(archivoTransmision, lineaTransmision)) {
            transmisiones.push_back(lineaTransmision);
        }
        archivoTransmision.close();
    }

    ofstream archivoSalida("checking.txt");

    if (!archivoCodigoMalicioso.is_open()) {
        cout << "Error al abrir el archivo de entrada" << endl;
        return 1;
    }

    if (!archivoSalida.is_open()) {
        cout << "Error al abrir el archivo de salida" << endl;
        return 1;
    }

    string lineaCodigo;

    while (getline(archivoCodigoMalicioso, lineaCodigo)) {
        string patron = lineaCodigo;
        archivoSalida << "Código: " << lineaCodigo << endl;

        vector<string> subsecuencias = generarSubsecuencias(patron);

        for (int j = 0; j < transmisiones.size(); ++j) {
            string texto = transmisiones[j];
            coincidencias = buscarKMP(texto, patron);

            archivoSalida << archivos[j] << " ==> " << coincidencias.size() << " veces " << endl;
            for (int k = 0; k < coincidencias.size(); k++) {
                archivoSalida << coincidencias[k];
                if (k != coincidencias.size() - 1) {
                    archivoSalida << ", ";
                }
            }
            archivoSalida << endl;
        }

        // Contar ocurrencias de subsecuencias
        for (const string& subsecuencia : subsecuencias) {
            for (int j = 0; j < transmisiones.size(); ++j) {
                int ocurrencias = contarCoincidencias(transmisiones[j], subsecuencia);

                if (ocurrencias > maxCoincidencias) {
                    maxCoincidencias = ocurrencias;
                    subsecuenciaMasFrecuente = subsecuencia;
                    archivoMasFrecuente = archivos[j];
                }
            }
        }

        archivoSalida << "La subsecuencia más encontrada es: " << subsecuenciaMasFrecuente
                      << " con " << maxCoincidencias << " ocurrencias en el archivo " 
                      << archivoMasFrecuente << endl;
        archivoSalida << "----------------------------" << endl;
        // Resetear para la siguiente iteración
        maxCoincidencias = 0;
        subsecuenciaMasFrecuente.clear();
        archivoMasFrecuente.clear();
    }

    // Mostrar el palíndromo más grande encontrado en cada transmisión
    archivoSalida << "==============" << endl;
    archivoSalida << "Palíndromo más grande:" << endl;
    for (int i = 0; i < transmisiones.size(); ++i) {
        string texto = transmisiones[i];
        vector<int> palindromo = obtenerPalindromoMasLargo(texto);
        archivoSalida << archivos[i] << " ==> " << "Posición: " << palindromo[0] << endl;
        archivoSalida << texto.substr(palindromo[0], palindromo[1]) << endl;
        if (i != (transmisiones.size() - 1)) {
            archivoSalida << "----" << endl;
        }
    }

    // Agregar la comparación de los substrings más largos (LCS)
    archivoSalida << "==============" << endl;
    archivoSalida << "Los Substring más largos son:" << endl;
    archivoSalida << "Transmission1 y Transmission2 ==> ";
    archivoSalida << obtenerLCS(transmisiones[0], transmisiones[1]) << endl;
    archivoSalida << "Transmission2 y Transmission3 ==> ";
    archivoSalida << obtenerLCS(transmisiones[1], transmisiones[2]) << endl;
    archivoSalida << "Transmission1 y Transmission3 ==> ";
    archivoSalida << obtenerLCS(transmisiones[0], transmisiones[2]) << endl;

    archivoCodigoMalicioso.close();
    archivoSalida.close();

    return 0;
}
