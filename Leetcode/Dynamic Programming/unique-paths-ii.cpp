/*
    63. Unique Paths II
    https://leetcode.com/problems/unique-paths-ii/
*/

class Solution {
public:
    int tabularSol(vector<vector<int>>& obstacleGrid) {
        const int M = obstacleGrid.size();
        const int N = obstacleGrid[0].size();
        
        vector<vector<long long>> dp(M, vector<long long>(N, 0));
        
        // starting point 
        dp[0][0] = obstacleGrid[0][0] == 1 ? 0 : 1;
        // 1st row and columns have only one way of reaching
        // for each cell we check if it is blocked or not, if not
        // then it can be reached in one way if previous cell is not blocked
        // 1st column
        for(int i = 1; i < M; i++)
            dp[i][0] = obstacleGrid[i][0] == 1 ? 0 : dp[i-1][0] == 1 ? 1 : 0;
        // 1st row
        for(int i = 1; i < N; i++)
            dp[0][i] = obstacleGrid[0][i] == 1 ? 0 : dp[0][i-1] == 1 ? 1 : 0;
        
        for(int i = 1; i < M; i++)
            for(int j = 1; j < N; j++)
                dp[i][j] = obstacleGrid[i][j] == 1 ? 0 :
                            dp[i-1][j] + dp[i][j-1];
        
        return dp[M-1][N-1];
    }
    
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        return tabularSol(obstacleGrid);   
    }
};
