https://www.codingninjas.com/studio/problems/975344

#include <bits/stdc++.h> 

int mem(int i, int j, vector<int>& arr, vector<vector<int>>& dp) {
    // base case
    if(i == j)
        return 0;

    if(dp[i][j] == INT_MAX) {
        for(int k = i; k < j; k++)
            dp[i][j] = min(dp[i][j], mem(i,k, arr, dp) + arr[i-1]*arr[k]*arr[j] + mem(k+1, j, arr, dp));
    }
    return dp[i][j];
}

int matrixMultiplication(vector<int> &arr, int n)
{
    // dp[i][j] = min no. of multiplications between matrix i and matrix j's chain
    // Also 0th index alone doesnt represent a matrix, matrix starts from index 1
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
    
    // memoization
    // return mem(1, n-1, arr, dp);

    for(int i = 0; i < n; i++)
        dp[i][i] = 0;

    for(int l = 1; l < n; l++) {
        // a matrix starts from index 1 and index 0 just has the row dimension for it
        for(int start = 1; start < n - l; start++) {
            int end = start + l;

            for(int k = start; k < end; k++) {
                // arr[start]'s dimension are stored in arr[start-1] * arr[start] 
                dp[start][end] = min(dp[start][end],
                                        dp[start][k] + arr[start-1] * arr[k]*arr[end] + dp[k+1][end]);
            }
        }
    }

    
    return dp[1][n-1];
}
