/*
    https://leetcode.com/problems/minimum-path-sum/
*/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if(grid.empty())
            return 0;
        
        const int M = grid.size(), N = grid.front().size();
        vector<vector<int>> dp(M, vector<int>(N, 0));
        
        // path value for starting position
        dp[0][0] = grid[0][0];
        // for 1st row only way to move is to move right
        for(int i = 1; i < N; i++)
            dp[0][i] = dp[0][i-1] + grid[0][i]; 
        // for 1st col, only way to move is to move down
        for(int i = 1; i < M; i++)
            dp[i][0] = dp[i-1][0] + grid[i][0];
        
        // for each position, we select the min path out of its 
        // top and left index
        for(int i = 1; i < M; i++) {
            for(int j = 1; j < N; j++) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[M-1][N-1];
    }
};
