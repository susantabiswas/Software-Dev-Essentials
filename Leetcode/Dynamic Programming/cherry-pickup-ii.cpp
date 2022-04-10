/*
    https://leetcode.com/problems/cherry-pickup-ii/
    
    TC: O(N^3)
    SC: O(N^3)
    
    This is very similar to https://leetcode.com/problems/cherry-pickup/.
    You can find the explanation for it here:
    https://leetcode.com/problems/cherry-pickup/discuss/1932198/C%2B%2B-Straight-forward-Top-down-DP-Detailed-Explanation
    
    The main thing to note is, the two paths depend on each other for their respective optimizations. So the naive way
    of finding the path once for each robot won't work, this is because the 1st robot might pick some cherries which might
    make the path for 2nd robot difficult collecting all the cherries. The paths need to decided from global maxima POV and
    not local maxima (greedy way). I have explained this concept in more details in the post for cherry pickup-1 problem.
    
    So we start the travesal together for both teh robots and the case to handle is when they are at the same position,
    the cherry should be added only once.
    
*/
class Solution {
public:
    bool isValid(int x, int y, int n_rows, int n_cols) {
        return x >= 0 && x < n_rows 
            && y >= 0 && y < n_cols;
    }

    int maxPath(int row, int y1, int y2,
               vector<vector<vector<int>>>& dp, vector<vector<int>>& grid) {
        // out of bound check
        if(!isValid(row, y1, grid.size(), grid[0].size()) 
           || !isValid(row, y2, grid.size(), grid[0].size()))
            return INT_MIN;
        
        if(dp[row][y1][y2] != -1)
            return dp[row][y1][y2];
        
        // Total cherries for their current positions
        int cherries = 0;
        if(y1 == y2)
            cherries = grid[row][y1];
        else
            cherries = grid[row][y1] + grid[row][y2];
        
        // check if the robots have hit the bottom row or not
        // both the robots will hit the bottom at the same time, 
        // since they travel the same effective distance
        if(row == grid.size()-1)
            return dp[row][y1][y2] = cherries;
        
        // There are 3*3 cmbs possible for col vals of two robots
        for(int col1 = -1; col1 <= 1; col1++)
            for(int col2 = -1; col2 <= 1; col2++)
                dp[row][y1][y2] = max(dp[row][y1][y2], maxPath(row + 1, y1 + col1, y2 + col2, dp, grid));
        dp[row][y1][y2] += cherries;
        
        return dp[row][y1][y2];
    }
    
    int cherryPickup(vector<vector<int>>& grid) {
        if(grid.empty())
            return 0;
        
        const int M = grid.size(), N = grid[0].size();
        // dp[row][y1][y2]: Max no. of cherries that can be collected when robots move from
        // (row, col1) & (row, col2)
        vector<vector<vector<int>>> dp(M, vector<vector<int>>(N, vector<int>(N, -1)));
        
        int total_cherries = maxPath(0, 0, N-1, dp, grid);
        return max(0, total_cherries);
    }
};
