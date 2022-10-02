/*
    https://leetcode.com/problems/maximum-sum-of-an-hourglass/
    
    TC: O(MN)
    SC: O(MN)
    
    Computing the hour glass is simple by iterating the hour glass elements, but
    if done for all positions in the grid, then we are doing repeatitive computations.
    
    To avoid that, we save the row and col wise cummulative sums. Then when we want to
    find the sum of hour glass, it is simply:
    sum(top hour glass row) + middle stem + sum(bottom hour glass row)
    Since we have the cummulative sum, we can use that to avoid computing the sum for
    each hour glass and instead return the sum in O(1).
*/
class Solution {
public:
    int maxSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // row_sum and col_sum saves the cummulative sum row and col
        // wise respectively.
        vector<vector<long long>> row_sum(m, vector<long long>(n, 0)), 
            col_sum(m, vector<long long>(n, 0));
        
        long long max_sum = 0;
         
        // Compute the cummulative sum row and col wise
        for(int r = 0; r < m; r++) {
            for(int c = 0; c < n; c++) {
                // row sum
                row_sum[r][c] = (c > 0 ? row_sum[r][c-1] : 0) + grid[r][c];
                // col sum
                col_sum[r][c] = (r > 0 ? col_sum[r-1][c] : 0) + grid[r][c];
            }
        }
        
        // find the max hour glass
        for(int r = 0; r < m; r++)
            for(int c = 0; c < n; c++) {
                // check if a hour glass is possible to compute
                if(r + 2 < m && c + 2 < n) {
                    long long sum = (row_sum[r][c+2] - (c > 0 ? row_sum[r][c-1] : 0)) + 
                                    grid[r+1][c+1] +
                                    (row_sum[r + 2][c+2] - (c > 0 ? row_sum[r + 2][c-1] : 0));
                    
                    max_sum = max(max_sum, sum);
                }
            }
        return max_sum;
    }
};
