/*
    https://leetcode.com/problems/count-square-submatrices-with-all-ones/
    
    The sq length ending at any position tells us about the number of squares that
    are possible with their bottom right corner at that point with length starting 1 to L, where L is the 
    value for that position. To account for each subsquare we can do incremental addition.
    So for any position i, j ending with L, we add L to total, which basically means we are counting
    all the squares with different lengths that can be formed at that corner.
    
    We will account for each square in this way since the cells top, diagonal up left and right would have
    already accounted for the squares that can be of possible lengths with their bottom right corner at those 
    positions.
*/
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        // We use the grid to store the length of maximum 
        // square ending at (i, j).
        int total_sq = 0;
        
        // 1st row: add the 1 length squares
        for(int i = 0; i < matrix[0].size(); i++)
            if(matrix[0][i])
                ++total_sq;
        
        // 1st col: add the 1 length squares
        for(int i = 1; i < matrix.size(); i++)
            if(matrix[i][0])
                ++total_sq;
        
        for(int i = 1; i < matrix.size(); i++)
            for(int j = 1; j < matrix[0].size(); j++) {
                // if the current pos is 1
                if(matrix[i][j]) {
                    matrix[i][j] = min({matrix[i-1][j-1],
                                            matrix[i][j-1],
                                            matrix[i-1][j]});
                    
                    // if the square ending at (i, j) has length 0,
                    // with the adjacent blocks, we can still make a sq of length 1
                    // since the current pos is 1
                    matrix[i][j] += 1;
                    total_sq += matrix[i][j];
                }
            }
             
         
        return total_sq;
    }
};
