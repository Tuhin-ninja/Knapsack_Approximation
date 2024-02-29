#include <bits/stdc++.h>
using namespace std;

#define INF 100000010

using MemoTable = vector<vector<int>>;

pair<int, vector<int>> minUtil(vector<pair<int, int>> &v, int n, int value, MemoTable &memo)
{
    if (value <= 0)
    {
        return {0, vector<int>()};
    }

    if (n == 0)
    {
        return {INF, vector<int>()};
    }

    if (memo[n][value] != -1)
    {
        return {memo[n][value], vector<int>()};
    }

    int exclude, include;
    vector<int> excludeIndices, includeIndices;

    auto ret1 = minUtil(v, n - 1, value, memo);
    exclude = ret1.first;
    excludeIndices = ret1.second;
    auto ret2 = minUtil(v, n - 1, value - v[n - 1].first, memo);
    include = ret2.first + v[n - 1].second;
    includeIndices = ret2.second;

    include += v[n - 1].second;
    if (include < exclude)
    {
        includeIndices.push_back(n - 1);
        memo[n][value] = include;
        return {include, includeIndices};
    }
    else
    {
        memo[n][value] = exclude;
        return {exclude, excludeIndices};
    }
}

pair<int,vector<int>>  minWeight(vector<pair<int, int>> &v, int n, int value)
{

    MemoTable memo(n + 1, vector<int>(value + 1, -1));
    return minUtil(v, n, value, memo);
}


int main(){
    freopen("in2.txt","r", stdin); 
    int n, w;
    cin >> n >> w;
    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i].first >> v[i].second;
    }

    auto ret = minWeight(v, n, w);
    cout << "Min weight: " << ret.first << endl;
    cout << "Indices: ";
    for(int i : ret.second){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}