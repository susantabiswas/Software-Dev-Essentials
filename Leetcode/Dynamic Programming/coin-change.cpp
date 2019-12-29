/*
    https://leetcode.com/problems/coin-change/submissions/
    
    We find the min no. of coins req for each amount lesser than equal to target.
    Then use those values for computing the next value.
    
    Initially the cache values are INF except for 0 target value which can
    be achieved with any no. of coins.
    Then for each target we check the min comb of coins for that
*/

class Solution {
public:
    // using 1D array
    int coinChangeTab(int amt, vector<int>& coins, vector<int>& dp) {
        dp[0] = 0;
        
        for(int i = 0; i <= amt; i++) {
            for(int coin: coins) {
                // when coin value is smaller/ equal to target
                if(coin <= i) {
                    int remain_val = dp[i - coin];
                    if(remain_val != INT_MAX)
                        remain_val += 1;
                    dp[i] = min(dp[i], remain_val);
                        
                }
            }
        }
        return dp.back() == INT_MAX ? -1: dp.back();
    }
    
    /*
    // using 2D array
    int coinChangeIter(vector<int>& coins, int& amount) {
        if(coins.empty() || amount <= 0)
            return 0;
        
        const int N = coins.size();
        vector<vector<int>> dp(N, vector<int>(amount + 1, INT_MAX));
        
        // for amount = 0, zero coins are req.
        for(int i = 0; i < N; i++)
            dp[i][0] = 0;
        
        // we calculate the coins req. when limiting the number of denominations
        for(int i = 0; i < N; i++) {
            // no. of coins req for each value with 'i' no. of denominations avail
            for(int j = 1; j <= amount; j++) {
                // min coins req using the previous denominations
                int min_coins_prev = (i-1) >= 0 ? dp[i-1][j] : INT_MAX;
                // if denomination is greater, use the previous denomination limit
                if(coins[i] > j)
                    dp[i][j] = min_coins_prev;
                else {
                    int min_coins_after_subtraction = dp[i][j - coins[i]];
                    min_coins_after_subtraction = min_coins_after_subtraction == INT_MAX ? INT_MAX :
                                                    1 + dp[i][j - coins[i]];
                    dp[i][j] = min(min_coins_after_subtraction,
                                  min_coins_prev);
                }
            }
        }
        
        return dp[N-1][amount] == INT_MAX ? -1 : dp[N-1][amount];
    }
    */
    
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);
        int ans = coinChangeTab(amount, coins, dp);
        
        return ans;
    }
};
