#include <bits/stdc++.h>
using namespace std;

#define INF 100000010
using MemoTable = vector<vector<int>>;

class Knapsack
{
public:
    // vector<int> subset_sum_indices(vector<int> &arr, int target)
    // {
    //     int n = arr.size();
    //     vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
    //     for (int i = 0; i <= n; ++i)
    //     {
    //         dp[i][0] = true;
    //     }

    //     for (int i = 1; i <= n; ++i)
    //     {
    //         for (int j = 1; j <= target; ++j)
    //         {
    //             if (j < arr[i - 1])
    //             {
    //                 dp[i][j] = dp[i - 1][j];
    //             }
    //             else
    //             {
    //                 dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
    //             }
    //         }
    //     }

    //     if (!dp[n][target])
    //     {
    //         return vector<int>();
    //     }

    //     vector<int> indices;
    //     int i = n, j = target;
    //     while (i > 0 && j > 0)
    //     {
    //         if (dp[i - 1][j])
    //         {
    //             --i;
    //         }
    //         else
    //         {
    //             indices.push_back(i);
    //             j -= arr[i - 1];
    //             --i;
    //         }
    //     }

    //     return indices;
    // }
    vector<int> knapsackIndices(int W, const vector<pair<int, int>> &items)
    {
        int n = items.size();
        vector<pair<int, int>> sortedItems;
        for(int i=0;i<n;i++) {
            sortedItems.push_back({items[i].second, items[i].first});
        }
        sort(sortedItems.begin(), sortedItems.end()); // Sort items based on weights

        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
        vector<vector<bool>> selected(n + 1, vector<bool>(W + 1, false));

        // Build DP table
        for (int i = 1; i <= n; ++i)
        {
            for (int w = 1; w <= W; ++w)
            {
                if (sortedItems[i - 1].first <= w)
                {
                    int include = sortedItems[i - 1].second + dp[i - 1][w - sortedItems[i - 1].first];
                    int exclude = dp[i - 1][w];
                    if (include > exclude)
                    {
                        dp[i][w] = include;
                        selected[i][w] = true;
                    }
                    else
                    {
                        dp[i][w] = exclude;
                    }
                }
                else
                {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        // Backtrack to find selected items
        vector<int> indices;
        int i = n, w = W;
        while (i > 0 && w > 0)
        {
            if (selected[i][w])
            {
                indices.push_back(i);
                w -= sortedItems[i - 1].first;
            }
            --i;
        }
        //reverse(indices.begin(), indices.end()); // Reverse the indices to get the correct order
        return indices;
    }

    int minWeightUtil(vector<pair<int, int>> &v, int n, int value, MemoTable &memo)
    {
        if (value <= 0)
        {
            return 0;
        }

        if (n == 0)
        {
            return INF;
        }
        if (memo[n][value] != -1)
        {
            return memo[n][value];
        }

        return memo[n][value] = min(minWeightUtil(v, n - 1, value, memo), v[n - 1].second + minWeightUtil(v, n - 1, value - v[n - 1].first, memo));
    }

    pair<int, vector<int>> minUtil(vector<pair<int,int>> &v, int n, int value, MemoTable &memo){
        if(value <= 0){
            return {0, vector<int>()};
        }

        if(n == 0){
            return {INF, vector<int>()};
        }

        if(memo[n][value] != -1){
            return {memo[n][value], vector<int>()};
        }

        int exclude , include; 
        vector<int> excludeIndices, includeIndices;

        auto ret1 = minUtil(v, n - 1, value, memo);
        exclude = ret1.first;
        excludeIndices = ret1.second;
        auto ret2 = minUtil(v, n - 1, value - v[n - 1].first, memo);
        include = ret2.first + v[n - 1].second;
        includeIndices = ret2.second;

        include += v[n - 1].second;
        if(include < exclude){
            includeIndices.push_back(n - 1);
            memo[n][value] = include;
            return {include, includeIndices};
        } else {
            memo[n][value] = exclude;
            return {exclude, excludeIndices};
        }
    }

    int   minWeight(vector<pair<int, int>> &v, int n, int value)
    {

        MemoTable memo(n + 1, vector<int>(value + 1, -1));
        return minWeightUtil(v, n, value, memo);
    }


    void knapsack_solve_approx(vector<pair<int, int>> v, int n, int w, double epsilon)
    {
        cout << "Rounded instance with epsilon = " << epsilon << endl;
        int maximum = 0;
        for (int i = 0; i < n; i++)
        {
            maximum = max(maximum, v[i].first);
        }

        double theta = (epsilon / (2 * n)) * maximum;
        cout << theta << endl;
        vector<pair<int, int>> pass;
        for (int i = 0; i < n; i++)
        {
            pass.push_back({ceil(v[i].first * 1.0 / theta), v[i].second});
        }

        knapsack_solve(pass, n, w);
    }

    void knapsack_solve(vector<pair<int, int>> &v, int n, int w)
    {
        vector<int> result;
        // for (int i = 0; i < n; i++)
        // {
        //     result.push_back(v[i].second);
        // }
        int prevWeight = 0;
        int value = 0, i = 0;
        vector<int> indices; 
        while (true)
        {
            int temp = minWeight(v, n, i);
            if (temp > w)
            {
                break;
            }
            //indices = minWeight(v, n, i).;
            prevWeight = temp;
            value = i;
            i++;
        }

        //vector<int> indices = knapsackIndices(w, v);
        cout << "Answer : " << value << endl;
        // int usedWeight = 0;
        // for (auto i : indices)
        // {
        //     usedWeight += v[i - 1].second;
        // }

        cout << "Used Weight : " << prevWeight << endl;

        cout << "Indices : ";
        for (auto i : indices)
        {
            cout << i << " ";
        }

        cout << endl;
    }
};