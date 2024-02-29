#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Function to solve the 0/1 knapsack problem and find the indices of selected items
pair<int, vector<int>> knapsackMaxValueMinWeightIndices(int W, const vector<int>& wt, const vector<int>& val) {
    int n = wt.size();
    vector<vector<pair<int, vector<int>>>> dp(n + 1, vector<pair<int, vector<int>>>(W + 1, {0, vector<int>()}));

    // Build DP table
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= W; ++w) {
            if (wt[i - 1] <= w) {
                int include = val[i - 1] + dp[i - 1][w - wt[i - 1]].first;
                int exclude = dp[i - 1][w].first;
                if (include > exclude) {
                    dp[i][w].first = include;
                    dp[i][w].second = dp[i - 1][w - wt[i - 1]].second;
                    dp[i][w].second.push_back(i - 1); // Include index of current item
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Find the maximum value and minimum weight among all solutions with the maximum value
    pair<int, vector<int>> maxValMinWeightIndices = {0, vector<int>()};
    for (int w = 0; w <= W; ++w) {
        if (dp[n][w].first > maxValMinWeightIndices.first) {
            maxValMinWeightIndices = dp[n][w];
        }
    }
    return maxValMinWeightIndices;
}

int main() {
    // Example vector of weights and values
    vector<int> wt = {100, 200, 300, 400};
    vector<int> val = {50, 100, 150, 200};

    // Capacity of the knapsack
    int W = 700;

    // Find the solution where the used weight is minimum among solutions with maximum value
    pair<int, vector<int>> result = knapsackMaxValueMinWeightIndices(W, wt, val);

    // Print the maximum value and the corresponding used weight
    cout << "Maximum value: " << result.first << endl;
    cout << "Indices of selected items: ";
    for (int index : result.second) {
        cout << index << " ";
    }
    cout << endl;

    return 0;
}
