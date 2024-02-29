#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to solve the 0/1 knapsack problem and find the indices of selected items
vector<int> knapsackIndices(int W, const vector<pair<int, int>>& items) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    vector<vector<bool>> selected(n + 1, vector<bool>(W + 1, false));

    // Build DP table
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= W; ++w) {
            if (items[i - 1].first <= w) {
                int include = items[i - 1].second + dp[i - 1][w - items[i - 1].first];
                int exclude = dp[i - 1][w];
                if (include > exclude) {
                    dp[i][w] = include;
                    selected[i][w] = true;
                } else {
                    dp[i][w] = exclude;
                }
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Backtrack to find selected items
    vector<int> indices;
    int i = n, w = W;
    while (i > 0 && w > 0) {
        if (selected[i][w]) {
            indices.push_back(i - 1);
            w -= items[i - 1].first;
        }
        --i;
    }
    reverse(indices.begin(), indices.end()); // Reverse the indices to get the correct order
    return indices;
}

int main() {
    int W = 10; // Capacity of the knapsack
    vector<pair<int, int>> items = {{5, 10}, {4, 40}, {6, 30}, {3, 50}}; // Pairs representing weight and value

    // Find the indices of selected items in the optimal solution
    vector<int> indices = knapsackIndices(W, items);

    // Print the indices
    cout << "Indices of selected items: ";
    for (int index : indices) {
        cout << index << " ";
    }
    cout << endl;

    return 0;
}
