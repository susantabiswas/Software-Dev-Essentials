/*
    96. Unique Binary Search Trees
    https://leetcode.com/problems/unique-binary-search-trees/submissions/
    
    For each N, we can have all cmb of all smaller elements on left and remaining
    greater N-i elements on right.
    
    so, C(n) = C(0).C(n-1) + C(1).C(n-2) +.....+C(n-1)C(0)
*/

class Solution {
public:
    // Top down solution
    int uniqueBSTMem(vector<int>& dp, int n) {
        // base case
        if(n <= 1)
            return 1;

        if(dp[n] == 0) 
            for(int i = 0; i < n; i++)
                dp[n] += uniqueBSTMem(dp, i) * uniqueBSTMem(dp, n-i-1);

        return dp[n];
    }

    // Bottom up solution
    int uniqueBSTTab(vector<int>& dp, int n) {
        dp[0] = dp[1] = 1;
        
        for(int i = 2; i <= n; i++) {
            for(int j = 0; j < i; j++) {
                dp[i] += dp[j] * dp[i-j-1];
            }
        }
        return dp[n];
    }
    
    int numTrees(int n) {
        // memoization table
        vector<int> dp(n+1, 0);

        //return uniqueBSTMem(dp, n);
        return uniqueBSTTab(dp, n);
    }
};
