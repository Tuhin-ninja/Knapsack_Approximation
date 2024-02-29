#include "header.hpp"



int main(){ 
   Knapsack knapsack;
   freopen("in2.txt","r", stdin); 
   int n, w;
    cin >> n >> w;
    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i].first >> v[i].second;
    }

    //knapsack.knapsack_solve(v, n, w);
    knapsack.knapsack_solve_approx(v, n, w, 0.5);
   
}
