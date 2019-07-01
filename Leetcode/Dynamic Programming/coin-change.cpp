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
    
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);
        int ans = coinChangeTab(amount, coins, dp);
        
        return ans;
    }
};
