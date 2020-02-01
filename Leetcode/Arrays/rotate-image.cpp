/*
    https://leetcode.com/problems/rotate-image/
    
    // Solution 1
    The idea is to shrink the matrix. We track the col and row starting and ending index. The
    start a simulation where we traverse the outer layer of the matrix and replace the values one by one in that
    layer. We continue the simulation by shrinking the dimension window.
    TC: O(N^2), SC: O(1)
    
    // Solution 2
    Transpose the matrix and reverse each row.
*/
class Solution {
public:
    // Solution 1
    void rotate1(vector<vector<int>>& matrix) {
        if(matrix.empty())
            return;
        
        const int M = matrix.size(), N = matrix[0].size();
        int row_start = 0, row_end = M - 1, col_start = 0, col_end = N - 1;
        
        while(row_start < row_end && col_start < col_end) {
            for(int i = 0; i < col_end - col_start; i++) {
                // get the values from each boundary side
                int first = matrix[row_start][col_start + i];
                int second = matrix[row_start + i][col_end];
                int third = matrix[row_end][col_end - i];
                int fourth = matrix[row_end - i][col_start];
                
                // replace the boundary values
                matrix[row_start + i][col_end] = first;
                matrix[row_end][col_end - i] = second;
                matrix[row_end - i][col_start] = third;
                matrix[row_start][col_start + i] = fourth;
            }  
            ++col_start, ++row_start, --col_end, --row_end;
        }
    }
    
    // Solution 2
    void rotate(vector<vector<int>>& matrix) {
        const int N = matrix.size();
        // transpose the matrix
        for(int i = 0; i < N; i++)
            for(int j = 0; j < i; j++)
                swap(matrix[i][j], matrix[j][i]);
        
        // reverse each row
        for(int i = 0; i < N; i++)
            reverse(matrix[i].begin(), matrix[i].end());
    }
    
};
