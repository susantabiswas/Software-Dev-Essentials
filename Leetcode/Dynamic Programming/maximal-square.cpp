/*
    https://leetcode.com/problems/maximal-square/submissions/
    
    We use a 2D dp, where each position stores the side of the
    max square ending at the current position. For finding the max square 
    ending at (i, j), we check the top left diagonal value, the top and left side values
    in the DP. The min value will be the max square that can end at (i, j).
    
    TC: O(MN)
    SC: O(MN)
*/
class Solution {
public:
    // Space optimised: using 1D array for DP
    // Since we only need the previous row values so, we use 2 1D arrays for that
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.empty())
            return 0;
        
        const int M = matrix.size(), N = matrix[0].size();
        // dp(i): side of largest sq whose ending corner is ith column in matrix
        // stores the values of previous row
        vector<int> prev(N, 0);
        int max_side = 0;
        
        for(int i = 0; i < M; i++) {
            // temporary DP array for storing the values in current row 'i'
            vector<int> curr(N, 0);
            for(int j = 0; j < N; j++) {
                // iff current position has 1, then only it can be part of sq.
                if(matrix[i][j] == '1') {
                    curr[j] = 1 + min({ prev[max(0, j - 1)], // top left diagonal
                                         curr[max(0, j - 1)],   // left
                                         prev[j]   // top
                                    });
                    /// update max seen side
                    max_side = max(max_side, curr[j]);
                }
            }
            // make the current row DP values as previous
            prev = move(curr);
        }
        return max_side * max_side;
    }
    
    // using 2D matrix as DP
    int maximalSquare2D(vector<vector<char>>& matrix) {
        if(matrix.empty())
            return 0;
        
        const int M = matrix.size(), N = matrix[0].size();
        // dp(i, j): side of largest sq whose ending corneris (i, j) 
        vector<vector<int> > dp(M, vector<int>(N, 0));
        int max_side = 0;
        
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++) {
                // iff current position has 1, then only it can be part of sq.
                if(matrix[i][j] == '1') {
                    dp[i][j] = 1 + min({ dp[max(0, i - 1)][max(0, j - 1)], // top left diagonal
                                         dp[i][max(0, j - 1)],   // left
                                         dp[max(0, i - 1)][j]   // top
                                    });
                    /// update max seen side
                    max_side = max(max_side, dp[i][j]);
                }
            }
        
        return max_side * max_side;
    }
};
