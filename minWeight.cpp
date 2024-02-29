#include<bits/stdc++.h>
using namespace std; 

#define INF 100000010 
using MemoTable = vector<vector<int>>;




vector<int> subset_sum_indices(vector<int>& arr, int target) {
    int n = arr.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = true;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= target; ++j) {
            if (j < arr[i - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            }
        }
    }

    if (!dp[n][target]) {
        return vector<int>();
    }

    vector<int> indices;
    int i = n, j = target;
    while (i > 0 && j > 0) {
        if (dp[i - 1][j]) {
            --i;
        } else {
            indices.push_back(i);
            j -= arr[i - 1];
            --i;
        }
    }

    return indices;
}



int minWeightUtil(vector<pair<int,int>> &v, int n, int value, MemoTable& memo) {
    if(value <= 0){ 
        return 0; 
    }

    if(n == 0){ 
        return INF; 
    }
    if (memo[n][value] != -1) {
        return memo[n][value];
    }
    
    return memo[n][value] = min(minWeightUtil(v,n-1,value,memo), v[n-1].second + minWeightUtil(v,n-1,value-v[n-1].first,memo));
}




int minWeight(vector<pair<int,int>> &v, int n, int value) {

    MemoTable memo(n + 1, vector<int>(value + 1, -1));
    return minWeightUtil(v, n, value, memo);

}



int main(){ 
   freopen("in2.txt","r", stdin); 
   int n, w;
    cin >> n >> w;
    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i].first >> v[i].second;
    }

    vector<int> result; 
    for(int i=0;i<n;i++) {
        result.push_back(v[i].first); 
    }


    int value = 0, i=0; 
    while(true){ 
        int temp = minWeight(v,n,i);
        if(temp > w){ 
            break; 
        }

        value = i; 
        i++;
    }

    vector<int> indices = subset_sum_indices(result, value);
    cout<<"Answer : "<<value<<endl; 
    int usedWeight = 0; 
    for(auto i : indices){ 
        usedWeight += v[i-1].second;
    }

    cout<<"Used Weight : "<<usedWeight<<endl;

    cout<<"Indices : "; 
    for(auto i : indices){ 
        cout<<i<<" "; 
    }

    cout<<endl; 

   
}
