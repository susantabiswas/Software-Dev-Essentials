/*
    https://leetcode.com/problems/spiral-matrix-ii/
    
    TC: O(n^2)
    SC: O(1)
*/
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> grid(n, vector<int>(n));
        
        int row_s = 0, row_e = n-1, col_s = 0, col_e = n-1;
        int num = 1;
        
        while(row_s <= row_e && col_s <= col_e) {
            // top row
            for(int c = col_s; c <= col_e; c++)
                grid[row_s][c] = num++;
            ++row_s;
            
            // right col
            for(int r = row_s; r <= row_e; r++)
                grid[r][col_e] = num++;
            --col_e;
            
            // bottom row
            for(int c = col_e; c >= col_s; c--)
                grid[row_e][c] = num++;
            --row_e;
            
            // left col
            for(int r = row_e; r >= row_s; r--)
                grid[r][col_s] = num++;
            ++col_s;
        }
        
        return grid;
    }
};
