/*
    https://practice.geeksforgeeks.org/problems/-minimum-number-of-coins/0
*/
#include<bits/stdc++.h>
using namespace std;

void solve(int& n) {
    if (n <= 0)
        return;

    vector<int> coins = { 1, 2, 5, 10, 20, 50, 100, 200, 500, 2000 };
    // dp(i): min coins to make sum i
    vector<vector<int>> dp(coins.size(), vector<int>(n + 1, INT_MAX));
    vector<int> change;

    // empty sum can be made with 0 coins
    for (int i = 0; i < coins.size(); i++)
        dp[i][0] = 0;

    for (int i = 0; i < coins.size(); i++) {
        for (int j = 1; j <= n; j++) {
            // For the current sum, either use the current coin
            // or don't use the current coin
            int without = i >= 1 ? dp[i - 1][j] : INT_MAX;
            int with = coins[i] <= j ? 1 + dp[i][j - coins[i]] : without;
            dp[i][j] = min(with, without);
        }
    }
    
    // find the coins used for making the optimal solution
    int i = dp.size() - 1, j = dp[0].size() - 1;
    while (i >= 0 && j >= 0) {
        if (j >= coins[i] && dp[i][j] == (dp[i][j - coins[i]] + 1)) {
            change.emplace_back(coins[i]);
            j = j - coins[i];
        }
        else {
            i -= 1;
        }
    }

    for (auto num : change)
        cout << num << " ";
    return;
}

ostream& operator<<(ostream& out, vector<int> nums) {
    for (auto num : nums)
        out << num << " ";
    return out;
}

int main()
{
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        solve(n);
        cout << endl;
    }
    return 0;
}