#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Función para calcular el array de prefijos "lps" (Longest Prefix Suffix) para el algoritmo KMP
vector<int> lps(string p) {
    int n = p.size();
    vector<int> lpsv(n, 0);
    int j = 0, i = 1;
    while (i < n) {
        if (p[i] == p[j]) {
            lpsv[i++] = ++j;
        } else {
            if (j == 0) {
                lpsv[i] = 0;
                i++;
            } else {
                j = lpsv[j - 1];
            }
        }
    }
    return lpsv;
}

// Implementación del algoritmo KMP para buscar un patrón en un texto
vector<int> kmp(string texto, string patron) {
    vector<int> posMatch;
    vector<int> lpsv = lps(patron);
    int j = 0, i = 0;
    int n = texto.length();
    int m = patron.length();

    while (i < n) {
        if (texto[i] == patron[j]) {
            i++;
            j++;
            if (j == m) {
                posMatch.push_back(i - m);
                j = 0;  // Reiniciar el patrón
            }
        } else {
            if (j == 0) {
                i++;
            } else {
                j = lpsv[j - 1];
            }
        }
    }
    return posMatch;
}

// Algoritmo de Manacher para encontrar el palíndromo más largo en un texto
vector<int> manacher(const string& s) {
    vector<int> Palindromo(2);
    string t = "#";
    for (char c : s) {
        t += c;
        t += '#';
    }

    int n = t.size();
    vector<int> p(n, 0);
    int c = 0, r = 0;
    int maxLen = 0;
    int centerIndex = 0;

    for (int i = 0; i < n; ++i) {
        int mirror = 2 * c - i;

        if (i < r) {
            p[i] = min(r - i, p[mirror]);
        }

        while (i + p[i] + 1 < n && i - p[i] - 1 >= 0 && t[i + p[i] + 1] == t[i - p[i] - 1]) {
            p[i]++;
        }

        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }

        if (p[i] > maxLen) {
            maxLen = p[i];
            centerIndex = i;
        }
    }

    int start = (centerIndex - maxLen) / 2;
    Palindromo[0] = start;
    Palindromo[1] = maxLen;
    return Palindromo;
}

// Algoritmo para encontrar el substring común más largo entre dos palabras (LCS)
string LCSStr(string palabra1, string palabra2) {
    int n = palabra1.length();
    int m = palabra2.length();
    vector<vector<int>> longitud(n + 1, vector<int>(m + 1, 0));
    int resultado = 0;
    int finresultado = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (palabra1[i - 1] == palabra2[j - 1]) {
                longitud[i][j] = longitud[i - 1][j - 1] + 1;
                if (longitud[i][j] > resultado) {
                    resultado = longitud[i][j];
                    finresultado = i;
                }
            } else {
                longitud[i][j] = 0;
            }
        }
    }
    return palabra1.substr(finresultado - resultado, resultado);
}

// Función para generar todas las subsecuencias del código con un carácter menos
vector<string> generarSubsecuencias(const string& codigo) {
    vector<string> subsecuencias;
    int n = codigo.size();
    for (int i = 0; i < n; ++i) {
        string subsecuencia = codigo.substr(0, i) + codigo.substr(i + 1);
        subsecuencias.push_back(subsecuencia);
    }
    return subsecuencias;
}

// Función para contar la cantidad de veces que aparece una subsecuencia en un texto usando KMP
int contarOcurrencias(const string& texto, const string& subsecuencia) {
    vector<int> matchPositions = kmp(texto, subsecuencia);
    return matchPositions.size();
}

int main() {
    vector<string> transmissions;  // Almacenar cada archivo de transmisión
    vector<int> Match;  // Almacenar las posiciones de los patrones en cada transmisión
    string subsecuenciaMasEncontrada;
    int maxOcurrencias = 0;
    string archivoConMasOcurrencias;  // Archivo con más ocurrencias

    ifstream codigoMalicioso("mcode.txt");
    string filenames[] = {"Transmission1.txt", "Transmission2.txt", "Transmission3.txt"};

    // Leer cada archivo de transmisión
    for (int i = 0; i < 3; ++i) {
        ifstream transmissionFile(filenames[i]);
        string transmission;
        while (getline(transmissionFile, transmission)) {
            transmissions.push_back(transmission);
        }
        transmissionFile.close();
    }

    ofstream outfile("checking.txt");

    if (!codigoMalicioso.is_open()) {
        cout << "Error al abrir el archivo de entrada" << endl;
        return 1;
    }

    if (!outfile.is_open()) {
        cout << "Error al abrir el archivo de salida" << endl;
        return 1;
    }

    string line;

    while (getline(codigoMalicioso, line)) {
        string pattern = line;
        outfile << "Código: " << line << endl;

        vector<string> subsecuencias = generarSubsecuencias(pattern);

        for (int j = 0; j < transmissions.size(); ++j) {
            string text = transmissions[j];
            Match = kmp(text, pattern);

            outfile << filenames[j] << " ==> " << Match.size() << " veces " << endl;
            for (int k = 0; k < Match.size(); k++) {
                outfile << Match[k];
                if (k != Match.size() - 1) {
                    outfile << ", ";
                }
            }
            outfile << endl;
        }

        // Contar ocurrencias de subsecuencias
        for (const string& subsecuencia : subsecuencias) {
            for (int j = 0; j < transmissions.size(); ++j) {
                int ocurrencias = contarOcurrencias(transmissions[j], subsecuencia);

                if (ocurrencias > maxOcurrencias) {
                    maxOcurrencias = ocurrencias;
                    subsecuenciaMasEncontrada = subsecuencia;
                    archivoConMasOcurrencias = filenames[j];
                }
            }
        }

        outfile << "La subsecuencia más encontrada es: " << subsecuenciaMasEncontrada
                << " con " << maxOcurrencias << " ocurrencias en el archivo " 
                << archivoConMasOcurrencias << endl;
        outfile << "----------------------------" << endl;
        // Resetear para la siguiente iteración
        maxOcurrencias = 0;
        subsecuenciaMasEncontrada.clear();
        archivoConMasOcurrencias.clear();
    }

    // Mostrar el palíndromo más grande encontrado en cada transmisión
    outfile << "==============" << endl;
    outfile << "Palíndromo más grande:" << endl;
    for (int i = 0; i < transmissions.size(); ++i) {
        string text = transmissions[i];
        vector<int> Palindromo = manacher(text);
        outfile << filenames[i] << " ==> " << "Posición: " << Palindromo[0] << endl;
        outfile << text.substr(Palindromo[0], Palindromo[1]) << endl;
        if (i != (transmissions.size() - 1)) {
            outfile << "----" << endl;
        }
    }

    // Agregar la comparación de los substrings más largos (LCSStr)
    outfile << "==============" << endl;
    outfile << "Los Substring más largos son:" << endl;
    outfile << "T1-T2 ==> " << LCSStr(transmissions[0], transmissions[1]) << endl;
    outfile << "T1-T3 ==> " << LCSStr(transmissions[0], transmissions[2]) << endl;
    outfile << "T2-T3 ==> " << LCSStr(transmissions[1], transmissions[2]) << endl;

    // Cerrar ambos archivos
    codigoMalicioso.close();
    outfile.close();


    return 0;
}