
/*

Sample 1 -Input
6
6 1 3 2 2 3
Sample 1 - Output
0.6

Sample 2 - Input
2
2 2 
Sample 2 - Input
impossible

Sample 3 - Input
5
4 0 2 1 2
Sample 3 -Output
0 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Function to check if a given fraction f can be achieved
bool canAchieveFraction(const vector<int>& helium, int n, double fraction) {
    for (int i = 0; i < n; i++) {
        // Check if current helium amount can fill at least fraction of the balloon
        if (helium[i] < fraction * (i + 1)) {
            return false; // Not enough helium to fill the balloon fractionally
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;

    vector<int> helium(n);
    for (int i = 0; i < n; i++) {
        cin >> helium[i];
    }


    // Sort helium amounts and balloons capacities (1 to n)
    sort(helium.begin(), helium.end());

        // First check if it's impossible to fill even the smallest balloon
    for (int i = 0; i < n; i++) {
        if (helium[i] > (i + 1)) {
            cout << "impossible" << endl;
            return 0;
        }
    }

    // Binary search for the maximum fraction
    double low = 0.0, high = 1.0, mid;
    double result = 0.0;
    
    while (high - low > 1e-7) {  // Precision up to 1e-6 as required
        mid = (low + high) / 2.0;
        if (canAchieveFraction(helium, n, mid)) {
            result = mid;  // Update result to the achievable mid value
            low = mid;     // Try for a larger fraction
        } else {
            high = mid;    // Try a smaller fraction
        }
    }

    // If result is 0, then the answer is "impossible"
    if (result == 0.0 && helium[0] == 0) {
        cout << "0" << endl;
    }
    else if(result == 0.0){
      cout<<"impossible"<<endl;
    }
    else {
        cout << fixed << setprecision(6) << result << endl;
    }

    return 0;
}
