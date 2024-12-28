/*
Dora has a set of s containing integers. In the beginning, she will put all integers in [l,r] into the set s.
That is , an integer x is initially contained in the set if and only if l<x<r
Then she allows you to perform the following  operations :

Select three distinct integers a, b and c from the set s, such that gcd(a,b) = gcd(b,c) = gcd(a,c) = 1.
Then remove these three integers from the set s

What is the maximum number of operations you can perform?

Recall that gcd(x,y) means the greatest commom divisor of integers x and y

Input 
Each test consist of multiple test cases. The first line contains a single integer t(1<t<500) - the number of test cases.
The description of test cases follows

The only line of each test case contains two integers l and r (1<l<r<1000) - the range of integers in the initial set

Output 
For eeach test case , output a single integer - the maximum number of operations you can perform

Examples 

Input
8
1 3
3 7
10 21
2 8
51 60
2 15
10 26
1 1000

Output
1
1
3
1
2
3
4
250

Note in the first case, you can choose a=1,b=2,c=3 in the only operation, since gcd(1,2) = gcd(2,3) = gcd(1,3) = 1
and then there are no more integers set, so no more ooperations can be performed

In the second test case , you can choose a = 3, b=5,c=7 in the only operation

In the third test case, you can choose a=11, b=19, c=20 in the first operation,
a=13, b=14,c=15, in the second operation and a=10, b=17, c=21 , in the third operation after three operations,
the set s contains the following integers: 12,16,18
It can be proven that it's impossible to perform more than 3 operations

*/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

// Función para calcular el máximo común divisor (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Función para calcular el número máximo de operaciones
int max_operations(int l, int r) {
    // Crear un conjunto con los números entre l y r, excluyendo los extremos
    vector<int> nums;
    for (int i = l + 1; i <= r; ++i) {
        nums.push_back(i);
    }

    int count_operations = 0;
    int n = nums.size();

    // Mientras haya al menos 3 números en el conjunto
    while (n >= 3) {
        bool found = false;

        // Buscar tres números a, b, c con gcd(a,b) = gcd(b,c) = gcd(a,c) = 1
        for (int i = 0; i < n - 2; ++i) {
            for (int j = i + 1; j < n - 1; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    int a = nums[i];
                    int b = nums[j];
                    int c = nums[k];

                    // Verificar si los gcd de cada par son iguales a 1
                    if (gcd(a, b) == 1 && gcd(b, c) == 1 && gcd(a, c) == 1) {
                        // Si encontramos un triplete válido, eliminar los números
                        nums.erase(nums.begin() + k);
                        nums.erase(nums.begin() + j);
                        nums.erase(nums.begin() + i);
                        count_operations++;
                        found = true;
                        n -= 3;  // Reducir el tamaño del vector
                        break;
                    }
                }
                if (found) break;
            }
            if (found) break;
        }

        // Si no encontramos un triplete válido, terminamos
        if (!found) {
            break;
        }
    }

    return count_operations;
}

int main() {
    int t;
    cin >> t;  // Leer número de casos de prueba
    
    vector<pair<int, int>> test_cases;  // Almacenar los casos de prueba
    
    // Leer todos los casos de prueba y almacenarlos
    for (int i = 0; i < t; ++i) {
        int l, r;
        cin >> l >> r;
        test_cases.push_back({l, r});
    }
    
    // Procesar todos los casos de prueba después de haber leído todos los inputs
    for (const auto& test_case : test_cases) {
        int l = test_case.first;
        int r = test_case.second;
        // Llamar a la función que calcula el número máximo de operaciones
        cout << max_operations(l, r) << endl;
    }
    
    return 0;
}
