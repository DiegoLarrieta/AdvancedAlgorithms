/*
You are a coach at your local university. There are n students under your supervision, the programming skill of the i-th student is ai
​

You have to create a team for a new programming competition. As you know, the more students some team has the more probable its victory is! So you have to create a team with the maximum number of students. But you also know that a team should be balanced. It means that the programming skill of each pair of students in a created team should differ by no more than 5.

Your task is to report the maximum possible number of students in a balanced team.

The first line of the input contains one intefer n (1<n<2*10^5)- the number of students 

The second line of the input contains n integers a1, a2...an(1<ai<10^9) where ai is a programming skill of the i-th student 

Output 
Print one integer -> the maximum possible number of students in a balanced team 
*/

/*
Input 
6
1 10 17 12 15 2

Output 
3


1 2 10 12 15 17
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int max_balanced_team(int n, vector<int>& skills) {
    // Ordenarlo de mayor a menor para iterar mas facil los punteros 
    sort(skills.begin(), skills.end());
    
    int start = 0; // Inicializar el puntero de inicio
    int max_students = 0; // Variable para guardar el tamaño máximo del equipo
    
    // Deslizar el puntero final a través del vector
    for (int end = 0; end < n; ++end) {
        // Asegurarse de que el subarray sea balanceado
        while (skills[end] - skills[start] > 5) {
            ++start; // Mover el puntero de inicio a la derecha
        }
        // Calcular el tamaño del subarray balanceado
        max_students = max(max_students, end - start + 1);
    }
    
    return max_students;
}

int main() {
    int n;
    cin >> n; // Leer el número de estudiantes
    
    vector<int> skills(n);
    for (int i = 0; i < n; ++i) {
        cin >> skills[i]; // Leer las habilidades de los estudiantes
    }
    
    // Calcular y mostrar el tamaño máximo del equipo balanceado
    cout << max_balanced_team(n, skills) << endl;
    
    return 0;
}