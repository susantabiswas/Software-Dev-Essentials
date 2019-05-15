/*
    96. Unique Binary Search Trees
    https://leetcode.com/problems/unique-binary-search-trees/submissions/
    
    For each N, we can have all cmb of all smaller elements on left and remaining
    greater N-i elements on right.
    
    so, C(n) = C(0).C(n-1) + C(1).C(n-2) +.....+C(n-1)C(0)
*/

class Solution {
public:
    int uniqueBST(vector<int>& dp, int n) {
        // base case
        if(n <= 1)
            return 1;

        if(dp[n] == 0) 
            for(int i = 0; i < n; i++)
                dp[n] += uniqueBST(dp, i) * uniqueBST(dp, n-i-1);

        return dp[n];
    }

    int numTrees(int n) {
        // memoization table
        vector<int> dp(n+1, 0);

        return uniqueBST(dp, n);
    }
};
