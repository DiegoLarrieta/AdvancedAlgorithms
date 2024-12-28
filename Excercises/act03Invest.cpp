/*
Luis Diego Dominguez Larrieta 
A01275640
Number of N cases : 2

Number of D days  : 3

Price for each day: 9
                    1
                    5
Case 2
Number of D days : 5

Price for each day:1
                   2
                   3
                   4
                   5

Sample Output 
Buy in 2, sell in 3
Buy in 1, sell in 5

Complejidad O(N)

*/

#include <iostream>
#include <vector>

using namespace std;


string calculateProfit(int days,vector<int>&prices){
  int min_price_index = 0;
  int max_profit = 0;

  int buy_day=0;
  int sell_day=0;

  for(int i = 1; i<days; i++){
    //Se calcula el profit de si se compran en min_price y vendemos en el dia i
    int profit = prices[i] - prices[min_price_index];

    //Si el profit es mayor que el maximo actual , actualizamos 

    if(profit > max_profit){
      max_profit = profit;
      buy_day = min_price_index + 1;
      sell_day = i + 1;
    }

    //Si encontramos un precio mas bajo se actualiza el dia de compra

    if(prices[i] < prices[min_price_index]){
      min_price_index = i;
    }
  }

  return "Buy in " + to_string(buy_day) + ", sell in  " + to_string(sell_day);

}

int main (){

  int cases,days;
  cin>>cases;

  vector<string> results;

  for(int i=0; i < cases ; i++){
    cin>>days;
    vector<int>prices(days);

    for(int j = 0; j<days; j++){
      cin>>prices[j];
    }

    results.push_back(calculateProfit(days, prices));
  }
  for (const string& result : results) {
    cout << result << endl;
  }

  return 0;
}