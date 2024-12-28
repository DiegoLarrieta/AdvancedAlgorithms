/*
Input
4 10
4 8 5 3
5 12 8 1

Ouput
13

Explanation: You can buy books 1 and 3. Their price is 4 + 5 = 9 and the number of pages 5 + 8 = 13
*/
/*
You are in a book shop which sells n different books. You know the price and number of pages of each book.
You have decided that the total price of your purchases will be at most  x. What is the maximum number of pages you can buy? You can buy each book at most once.

Input
The first input line contains two integers n and x : the number of books and the maximumn total price

The next line contains n integers h1,h2,...,hn : the price of each book

The last line contains n integers s1,s2,...,sn : the number of pages of each book

Output 
Print one integer: the maximum number of pages

Constraints 
1 < n <= 1000
1 < x <= 10^5
1 < h1,si < 1000
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    
    vector<int> prices(n);
    vector<int> pages(n);
    
    for (int i = 0; i < n; i++) {
        cin >> prices[i];
    }
    
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }
    
    // DP array to store the maximum number of pages for every possible total price
    vector<int> dp(x + 1, 0);
    
    // Process each book
    for (int i = 0; i < n; i++) {
        int price = prices[i];
        int page = pages[i];
        
        // Traverse backwards to avoid using the same book multiple times
        for (int j = x; j >= price; j--) {
            dp[j] = max(dp[j], dp[j - price] + page);
        }
    }
    
    // The answer is the maximum number of pages we can obtain with total price <= x
    cout << dp[x] << endl;
    
    return 0;
}
