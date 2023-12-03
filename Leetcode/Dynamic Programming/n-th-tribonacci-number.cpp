/*
    https://leetcode.com/problems/n-th-tribonacci-number/
    
    TC: O(n)
    SC: O(1)
    
    Track the last 3 consecutive terms and use them to find the current term.
    Then just update the previous terms.
*/
class Solution {
public:
    int tribonacci(int n) {
        if(n <= 1)
            return n;
        if(n == 2)
            return 1;
        
        // 0-2 terms track the previous three consecutive terms
        // dp[3] = current tribonacci term
        vector<int> dp(4, 0);
        dp[0] = 0, dp[1] = 1, dp[2] = 1;
        
        for(int i = 3; i <= n; i++) {
            dp[3] = dp[2] + dp[1] + dp[0]; // 4th = 3rd + 2nd + 1st
            
            // update the previous consecutive terms
            dp[0] = dp[1];
            dp[1] = dp[2];
            dp[2] = dp[3];
        }
        return dp[3];
    }
};
