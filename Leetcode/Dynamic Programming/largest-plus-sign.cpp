/*
    https://leetcode.com/problems/largest-plus-sign/
    
    Idea is to find the max continuous length of 1s in each direction. Then at 
    each position, the max length plus that can be formed is limited by the smallest side
    length.
    TC: O(n^2)
*/

class Solution {
private:
    struct Neighbours {
        // Number of 1s in the diff directions starting current pos
        int left = 1, right = 1, top = 1, bottom = 1;
        // Mine: true, No Mine: false
        bool is_mine = false;
        // Sets the directional values to 0 due to mine
        void SetMine() {
            left = right = top = bottom = 0;
            is_mine = true;
        }
    };
    
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        // dp[i][j] = {max side lengths for each direction: left, top, right, bottom}
        vector<vector<Neighbours>> dp(n, vector<Neighbours>(n));
        
        // Mark all positions with a mine
        for(auto &pos: mines) 
            dp[pos[0]][pos[1]].SetMine();
        
        // plus with the largest side
        int largest_plus = 0;
        
        // Find the max length sides for top and left directions
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                // top side max continuous length
                if(i-1 >= 0)
                    dp[i][j].top = !dp[i][j].is_mine ? dp[i-1][j].top + 1 : 0;
                // left side max continuous length
                if(j-1 >= 0)
                    dp[i][j].left = !dp[i][j].is_mine ? dp[i][j-1].left + 1 : 0;
            }
        }
        
        // Find the max length sides for right and bottom directions
        for(int i = n-1; i >= 0; i--) {
            for(int j = n-1; j >= 0; j--) {
                // bottom side max continuous length
                if(i+1 < n)
                    dp[i][j].bottom = !dp[i][j].is_mine ? dp[i+1][j].bottom + 1 : 0;
                // right side max continuous length
                if(j+1 < n)
                    dp[i][j].right = !dp[i][j].is_mine ? dp[i][j+1].right + 1 : 0; 
                // Limiting side length
                largest_plus = max(largest_plus, min({dp[i][j].top, dp[i][j].bottom,
                                                      dp[i][j].left, dp[i][j].right}));
             }
        }
        return largest_plus;
    }
};
