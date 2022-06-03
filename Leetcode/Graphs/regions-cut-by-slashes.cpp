/*
    https://leetcode.com/problems/regions-cut-by-slashes/
    
    TC: O(N^2)
    SC: O(N^2)
    
    Idea is to map the grid pixels to a higher resolution matrix. Doing so gives the 
    necessary space between the pixels for traversal and figuring clear boundaries.
    
    For each slash value, we map it to a 3 * 3 grid, where three 1s are used to represent it.
    Eg: '/'
    001
    010
    100
    
    '\'
    100
    010
    001
    
    ["/ ", "\\ "]
    001000
    010000
    100000
    100000
    010000
    001000
    
    The empty spaces are clearly represented with 0s and they can be traversed also since they
    are connected together.
    Then this problem becomes problem of finding connected components of 0s. All the slash pixels (1s)
    form the border/obstructions in the traversal of 0s.
    Problem becomes similar to https://leetcode.com/problems/number-of-islands/
*/
class Solution {
public:
    void dfs(int row, int col, vector<vector<int>>& matrix) {
        // out of bound + already visited check (mark the empty with 1 to indicate visited)
        if(row < 0 || row >= matrix.size() || col < 0 ||
           col >= matrix.size() || matrix[row][col] == 1)
            return;
        // mark visited
        matrix[row][col] = 1;
        
        dfs(row + 1, col, matrix);
        dfs(row - 1, col, matrix);
        dfs(row, col + 1, matrix);
        dfs(row, col - 1, matrix);
    }
    
    int regionsBySlashes(vector<string>& grid) {
        int N = grid.size();
        
        // Map the graph cells to a higher resolution grid
        // Each cell is given 3 * 3 area. This would allow to have clear
        // boundary cells between the slashes
        // matrix[i][j] = 0 => Empty cell, 1 => a Pixel value of slash is present
        vector<vector<int>> matrix(N * 3, vector<int>(N * 3, 0));
        
        // fill the new higher resolution matrix
        for(int row = 0; row < N; row++)
            for(int col = 0; col < N; col++) {
                if(grid[row][col] == '/') {
                    matrix[row * 3][col * 3 + 2] = 1;
                    matrix[row * 3 + 1][col * 3 + 1] = 1;
                    matrix[row * 3 + 2][col * 3] = 1;
                }
                // '\\' is read at once and not as individual chars
                else if(grid[row][col] == '\\') {
                    matrix[row * 3][col * 3] = 1;
                    matrix[row * 3 + 1][col * 3 + 1] = 1;
                    matrix[row * 3 + 2][col * 3 + 2] = 1;
                }
            }
        
        // Now the pixel values of slashes which are represented by 1 act as boundary in 
        // the matrix. So now the matrix is filled with 0s and 1s, 0s are the empty spaces 
        // and 1s bound the empty space (0s). We now have to find the empty spaces connected to each other
        // either horizontally or vertically.
        int regions = 0;
        
        for(int row = 0; row < matrix.size(); row++)
            for(int col= 0; col < matrix.size(); col++) 
                if(matrix[row][col] == 0) {
                    dfs(row, col, matrix); 
                    ++regions;
                }
            
        return regions;
    }
    
};
