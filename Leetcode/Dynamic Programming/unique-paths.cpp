/*
    62. Unique Paths
    https://leetcode.com/problems/unique-paths/

    Brute Force:
    Time Complexity : O(2^(m+n)), where m and n are the dimensions of the grid
        For each position we have two choices - left and top
        t(i) = 2t(i-1)
        ~ O(2^i)
        i = m + n, the max path length is rows + cols, since we can only move in down or right 
    Space Complexity : O(m+n), required by recursion stack

    DP:
    TC: O(mn)
    SC: O(m+n)

*/

class Solution {
public:
    // using memoization
    int memoizationSol(int m, int n, vector<vector<int>>& dp) {
        if(m == 0 && n == 0)
            return 1;
        if(m < 0 || n < 0)
            return 0;
        
        if(dp[m][n] == 0) {
            // only way to reach is from left or top
            dp[m][n] = memoizationSol(m-1, n, dp) + memoizationSol(m, n-1, dp);
        }
        return dp[m][n];
    }
    
    // using tabular approach
    int tabularSol(int& m, int& n) {
        vector<vector<int> > dp(m, vector<int>(n, 0));
        
        // there is only way to reach from top row and 1st column
        for(int i = 0; i < m; i++) 
            dp[i][0] = 1;
        for(int i = 0; i < n; i++)
            dp[0][i] = 1;
        
        for(int i = 1; i < m; i++)
            for(int j = 1; j < n; j++)
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
        
        return dp[m-1][n-1];
    }
    
    int uniquePaths(int m, int n) {
        //vector<vector<int> > dp(m, vector<int>(n, 0));
        //return memoizationSol(m-1, n-1, dp);
        
        return tabularSol(m, n);
    }
};
