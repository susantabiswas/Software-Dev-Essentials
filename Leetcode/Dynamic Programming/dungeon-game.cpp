/*
    https://leetcode.com/problems/dungeon-game/submissions/
*/

class Solution {
public:
    /*
        Since the objective is to find the min val such that
        path never sees a negative value, so if we start from top,
        we can't guarantee of finding a value which is min such that -ve
        never happens, at most we can a +ve val that can make that possible
        So we start from the destination cell and go towards the start.
        For each cell we find the min value that is needed if we have to reach the destination
        from that cell. Also each cell contribute to its right and down cells.
        So that value is simply the min value req to make 
        dungeon(i, j) + min(dungeon(i,j+1), dungeon(i+1, j)) = +ve
        Since we start from destination cell we can have an initial value for the health, 
        which is 1 in best case scenario. 
    */
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        if(dungeon.empty())
            return 0;
        
        const int M = dungeon.size(), N = dungeon.front().size();
        vector<vector<int>> dp(M, vector<int>(N, INT_MAX));
        
        for(int i = M - 1; i >= 0; i--) {
            for(int j = N - 1; j >= 0; j--) {
                // if current dungeon value is +ve then, then below becomes negative so we can take
                // 1(min value for survival), if current dungeon val is negative then we calculate 
                // the additional value req for current cell on top of min health for the contributing cells.
                if(i == M - 1 && j == N - 1)
                    dp[i][j] = max(1, 1 - dungeon[i][j]);
                else if(i == M - 1) // last row, each cell can allow movement towards right
                    dp[i][j] = max(1, dp[i][j+1] - dungeon[i][j]);
                else if(j == N - 1) // last column, each cell can allow movement towards bottom
                    dp[i][j] = max(1, dp[i+1][j] - dungeon[i][j]);
                else    // select the cell in left or right which requires least value 
                    dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j]);
            }
        }
        
        return dp[0][0];
    }
};
