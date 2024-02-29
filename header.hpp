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
    pair<int, vector<int>> knapsackMaxValueMinWeightIndices(int W, const vector<int> &wt, const vector<int> &val)
    {
        int n = wt.size();
        vector<vector<pair<int, vector<int>>>> dp(n + 1, vector<pair<int, vector<int>>>(W + 1, {0, vector<int>()}));

        // Build DP table
        for (int i = 1; i <= n; ++i)
        {
            for (int w = 1; w <= W; ++w)
            {
                if (wt[i - 1] <= w)
                {
                    int include = val[i - 1] + dp[i - 1][w - wt[i - 1]].first;
                    int exclude = dp[i - 1][w].first;
                    if (include > exclude)
                    {
                        dp[i][w].first = include;
                        dp[i][w].second = dp[i - 1][w - wt[i - 1]].second;
                        dp[i][w].second.push_back(i); // Include index of current item
                    }
                    else
                    {
                        dp[i][w] = dp[i - 1][w];
                    }
                }
                else
                {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        // Find the maximum value and minimum weight among all solutions with the maximum value
        pair<int, vector<int>> maxValMinWeightIndices = {0, vector<int>()};
        for (int w = 0; w <= W; ++w)
        {
            if (dp[n][w].first > maxValMinWeightIndices.first)
            {
                maxValMinWeightIndices = dp[n][w];
            }
        }
        reverse(maxValMinWeightIndices.second.begin(), maxValMinWeightIndices.second.end());
        return maxValMinWeightIndices;
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


    int minWeight(vector<pair<int, int>> &v, int n, int value)
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

        vector<int> wt, val; 
        for (int i = 0; i < n; i++)
        {
            wt.push_back(v[i].second);
            val.push_back(v[i].first);
        }
        int prevWeight = 0;
        int value = 0, i = 0;
        while (true)
        {
            int temp = minWeight(v, n, i);
            if (temp > w)
            {
                break;
            }
            // indices = minWeight(v, n, i).;
            prevWeight = temp;
            value = i;
            i++;
        }

        vector<int> indices = knapsackMaxValueMinWeightIndices(w,wt, val).second;
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