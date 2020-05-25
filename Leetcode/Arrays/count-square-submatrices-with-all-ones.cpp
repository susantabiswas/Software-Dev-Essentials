/*
    https://leetcode.com/problems/count-square-submatrices-with-all-ones/
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
