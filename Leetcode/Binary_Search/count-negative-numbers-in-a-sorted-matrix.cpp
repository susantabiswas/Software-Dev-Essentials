/*
	https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/
	TC: O(M + N)
*/

class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        if(grid.empty())
            return 0;
        // Since the rows and columns are sorted.
        // Top left element is greater than all its left and down elements
        // and also every element that occur in that region.
        // So to reduce the time complexity we need to prune, we do the 
        // processing row-wise. We start with the greatest element of smallest row.
        const int M = grid.size(), N = grid[0].size();
        int row = M-1, col = 0;
        int neg_count = 0;
        
        while(row >= 0 && col < N) {
            // if the current is neg, all its left are neg as well
            // We check if the same can be said about its upper element in above row
            if(grid[row][col] < 0) {
                neg_count += N - col;
                --row;
            }
            else
                ++col;
        }
        return neg_count;
    }
};
