/*
    https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
    TC: O(MN), SC: O(MN)

    Naive intuition fails: 
    Combine the result of longest path of max(
        longest_path(top to bottom and left to right),
        longest_path(bottom to up and from right to left)
    )

    The reason this fails is because the path is frozen, in the 1st iteration we are
    only finding a path moving either top to bottom or left to right.
    In the second iteration we are only moving from bottom to top or
    right to left.

    Now what if the path is like below
    --xx
    --x-
    --x-
    --xx

    top right wont be covered as part of the 2nd iteration and the longest path will be missed.
*/

class Solution {
public:
    bool isValid(int i, int j, int M, int N) {
        // boundary checking
        if(i < 0 || i >= M || j < 0 || j >= N)
            return false;
        return true;
    }
    
    // finds the longest path starting a particular position
    int searchLongestPath(vector<vector<int>>& dp, 
                          vector<vector<int> >& matrix, 
                          int i, int j) {
        
        if(dp[i][j] == 0) {
            // each element always has min length of 1
            dp[i][j] = 1;
            // move in all 4 directions
            // move up
            int up = isValid(i-1, j, dp.size(), dp[0].size()) &&
                     matrix[i-1][j] > matrix[i][j] ? 
                     1 + searchLongestPath(dp, matrix, i-1, j) : 0;
            // move right
            int right = isValid(i, j+1, dp.size(), dp[0].size()) &&
                         matrix[i][j+1] > matrix[i][j] ?
                         1 + searchLongestPath(dp, matrix, i, j+1) : 0;
            // move down
            int down = isValid(i+1, j, dp.size(), dp[0].size()) &&
                       matrix[i+1][j] > matrix[i][j] ?
                       1 + searchLongestPath(dp, matrix, i+1, j) : 0;
            // move left
            int left = isValid(i, j-1, dp.size(), dp[0].size()) &&
                       matrix[i][j-1] > matrix[i][j] ?
                       1 + searchLongestPath(dp, matrix, i, j-1) : 0;
            
            dp[i][j] = max({dp[i][j], up, right, down, left});
        }
        return dp[i][j];
    }
    
    // Finds the longest path in matrix
    // TC: O(MN), SC: O(MN)
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.empty())
            return 0;
        
        // We will use DP for this
        const int M = matrix.size(), N = matrix[0].size();
        // dp(i, j): max path length starting at (i, j)
        vector<vector<int> > dp(M, vector<int>(N, 0));
        int max_len = 1;
        
        // for each loaction, find the max path starting there
        for(int i = 0; i < M; i++) 
            for(int j = 0; j < N; j++)
                max_len = max(max_len, searchLongestPath(dp, matrix, i, j));
        
        return max_len;
    }
};
