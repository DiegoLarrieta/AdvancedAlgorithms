/*
Input 
4
3
2 1 3
4
1 1 1 1
5
4 2 3 1 5
4
1 2 1 2


Output
3
0
14
5

*/
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>
#include <unordered_map>
 
#define PI 3.141592653589793
#define EPS 0.000000001
#define INF 1000000000
 
#define _ ios_base::sync_with_stdio(0), cin.tie(0), cin.tie(0), cout.tie(0), cout.precision(15);
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define RFOR(i, a, b) for(int i=int(a)-1; i>=int(b); i--)
#define FORC(cont, it) for(typeof((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define RFORC(cont, it) for(typeof((cont).rbegin()) it = (cont).rbegin(); it != (cont).rend(); it++)
#define pb push_back
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
 
#define MAXN 10
#define MOD 1000000007

ll makePalindrome(vi & nums) {
    ll moves = 0;
    ll left = 0;
    ll right = nums.size()-1;

    while (left < right) {
        if (nums[left] == nums[right]) {
            left++;
            right--;
        } else if (nums[left] < nums[right]) {
            nums[left+1] = nums[left] + nums[left+1];
            left++;
            moves++;
        } else {
            nums[right-1] = nums[right] + nums[right-1];
            right--;
            moves++;
        }
    }

    return moves;
}

void solve(vi & nums) {
    if (nums.size() == 1) {
        cout << 0 << endl;
        return;
    }
    
    vi temp(nums.begin()+1, nums.end()-1);
    int ans = 0;
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < nums.size()-i; j++) {
            vi temp(nums.begin()+j, nums.end()-i);
            ans += makePalindrome(temp);
        }
    }

    cout << ans << endl;
}
 
int main() { _
    int t,n,a;
    cin >> t;

    while (t--) {
        cin >> n;
        vi nums;
        while (n--) {
            cin >> a;
            nums.pb(a);
        }
        solve(nums);
    }
    return 0;
}


/*
El output de este codigo es
4
0
25
5
El output esta incorrecto
*/