/*
Sakurako will soon take a test, The test can described as an array of integers n and a task on it:

Given an integer x, Sakurako can perform the folllowing operation any number of times

-Choose an inteher i(1<i<n) such that ai > xi
-Change the value of ai to ai - x

Using this operation any number of times, she must find the minimum possible median of the array a

Sakurako knows the array but does not know the integer x.
Someone let it slip that one of the q values of x will be in the next test, so Sakurako is asking you what the answer is for each such x

Input
The first line contains one integer (1<t<10^4) -> the number of test cases

The first line of each test case contains two integers n and q (1<n,q<10^5) -> the number of elements in the array and the number of queries

The second line of each test case contains n integers a1,a2,...,an(1<a<n) -> the elements of the array 

The following q lines each contain one integer x(1<x<n)

It is guaranteed that the sum of n across all the test cases does not exceed 10^5. The same guarantee applies to the sum of q across all test cases

Output

For each test case output q integers - the answer for each query 

Examples
Input
2
5 5
1 2 3 4 5
1
2
3
4
5
6 3
1 2 6 4 1 3
2
1
5

Output
0 1 1 1 2 
1 0 2
*/  

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Función para encontrar la mediana mínima posible dado el valor de x
int min_median_after_operations(vector<int>& a, int x) {
    int n = a.size();
    vector<int> modified_array = a;
    
    // Aplicar la operación: reducir los valores mayores que x
    for (int i = 0; i < n; ++i) {
        if (modified_array[i] > x) {
            modified_array[i] = x;
        }
    }
    
    // Ordenar el array modificado para encontrar la mediana
    sort(modified_array.begin(), modified_array.end());
    
    // Calcular la posición de la mediana
    int median_pos = (n - 1) / 2;  // La mediana está en la posición (n-1)/2 para arrays impares o pares
    
    // Devolver el valor de la mediana en la posición calculada
    return modified_array[median_pos];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t; // Leer número de casos de prueba

    // Procesar cada caso de prueba
    for (int i = 0; i < t; ++i) {
        int n, q;
        cin >> n >> q; // Leer tamaño del array y número de consultas
        vector<int> a(n);
        
        // Leer los elementos del array
        for (int j = 0; j < n; ++j) {
            cin >> a[j];
        }

        // Procesar las consultas
        for (int j = 0; j < q; ++j) {
            int x;
            cin >> x; // Leer el valor de x para la consulta
            cout << min_median_after_operations(a, x) << " ";
        }
        cout << endl; // Imprimir el resultado de todas las consultas de este caso
    }

    return 0;
}

