/*
    70. Climbing Stairs
    https://leetcode.com/problems/climbing-stairs/
*/

class Solution {
public:
    
    /// using memoization
    int waysStairs(int n, vector<int>& dp) {
        if(n < 0)
            return 0;
        if(n == 0)
            return 1;
        
        if(dp[n] == 0) {
            dp[n] = waysStairs(n-1, dp) + waysStairs(n-2, dp);
        }
        return dp[n];
    }
    
    // using tabular approach
    int waysStairsTab(int n, vector<int>& dp) {
        if(n == 0 || n == 1)
            return n;
        
        dp[1] = 1;
        dp[2] = 2;
        
        for(int i = 3; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
    
    int climbStairs(int n) {
        vector<int> dp(n+1, 0);
        //return waysStairs(n, dp);
        return waysStairsTab(n, dp);
    }
};
