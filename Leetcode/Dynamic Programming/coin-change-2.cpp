/*
    https://leetcode.com/problems/coin-change-2/submissions/
    
    // gives combination(without repeatition, [1,2])
    For(coin: coins):
        For(int I = 1; I <= total; i++)
            Dp[i] += dp[I - coin]

    // gives permutation ([1,2], [2,1])
    For(int I = 1; I <= total; i++)
        For(coin: coins)
            Dp[i] += dp[I -coin]
    In 2nd code:
    In each outer iteration, inner loop is just adding all possible combinations of previous with current coin: [coin, other_prev_cmb]
    So whenever we have coin pairs that exists, then they give the same combination of numbers but with different pos.
    Eg: [1,2,5], amount : 3
    For coin 1: [1, 2], [1,1,1]
    For coin 2: [2, 1]
    [1,2] and [2,1] are using same numbers in diff order

    Eg: how interchanging the loop afffects the solution
    https://leetcode.com/problems/coin-change-2/discuss/141076/Logical-Thinking-with-Clear-Java-Code/260611
*/
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        // dp(i): no. of cmb of getting sum i
        vector<unsigned int> dp(amount + 1, 0);
        dp[0] = 1;
        
        
        for(const int& coin : coins) 
            for(int i = coin; i <= amount; i++)
                dp[i] += dp[i - coin];

            return dp[amount];
    }
};
