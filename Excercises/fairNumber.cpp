/*
We call a positive integer number fair, if it is divisible by each of its nonzero digits.
For example , 102 is fair (because it is divisible by 1 and 2), but 282 is not , because it isnt divisible by 8.
Given a positive integer n., Find the minimum integer x, such that n>x and x is fair

Input
The first line contains number of test cases
Each of the t lines contains an integer n,}

Output

For each of the t test cases print a single integer- the least fair number , which is not less than n

Example

Input
4
1
282
1234567890
1000000000000000000

Output
1 
288
1234568040
1000000000000000000

Explanation 
In the first case number 1 is fair itself

In the second test case number 288 is fair(its divisible by both 2 and 8)
None of the numbers from [282,287] is fait , because for example none of them is divisible by 8

*/

#include<iostream>
#include<vector>

using namespace std;

// Función que determina si un número es "justo"
bool isFairNumber(long long num) {
    long long original = num;
    
    // Revisar cada dígito del número
    while (num > 0) {
        int digit = num % 10;
        if (digit != 0 && original % digit != 0) {
            return false;
        }
        num /= 10;
    }
    
    return true;
}

int main() {
    int t;
    cin >> t; // Leer el número de casos de prueba
    
    vector<long long> results; // Vector para almacenar los resultados
    
    while (t--) {
        long long n;
        cin >> n;
        
        // Empezamos desde el número n y buscamos el siguiente número "justo"
        while (!isFairNumber(n)) {
            n++;
        }
        
        // Agregamos el resultado al vector
        results.push_back(n);
    }
    
    // Imprimir todos los resultados
    for (long long res : results) {
        cout << res << endl;
    }
    
    return 0;
}