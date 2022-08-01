/*
    https://leetcode.com/problems/range-sum-query-2d-mutable/
    
    Very similar to 1 D BIT range sum. The only change here is we iterate
    for both row and col.
    
    You can find the explanation for 1D Binary Indexed Tree here
    https://leetcode.com/problems/range-sum-query-mutable/discuss/2359085/C%2B%2B-Clean-Segment-Tree-and-Binary-Indexed-Tree-solutions-Detailed-Explanation
    
    TC:
    Build: O(MNlog(MN))
    Query: O(logM * logN)
    Update: O(logM * logN)
    
    SC:
    O(MN)
*/
class NumMatrix {
    vector<vector<int>> bit, nums;
    int rows = 0, cols = 0;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        this->rows = matrix.size(), this->cols = matrix[0].size();
        this->nums = matrix;
        // To support 1 based indexing, adding 1 extra to row and col
        bit.resize(rows + 1, vector<int>(cols + 1, 0));
        
        // Build BIT from initial matrix
        for(int row = 0; row < rows; row++)
            for(int col = 0; col < cols; col++)
                updateBIT(row+1, col+1, matrix[row][col]);
    }
    
    void updateBIT(int r, int c, int delta) {
        // Similar to 1D Bit update, here we go ahead with both row and col 
        for(int row = r; row <= rows; row += (row & -row)) 
            for(int col = c; col <= cols; col += (col & -col))  
                bit[row][col] += delta;
    }
    
    int queryBIT(int r, int c) {
        int sum = 0;
        
        for(int row = r; row > 0; row -= (row & -row)) 
            for(int col = c; col > 0; col -= (col & -col))
                sum += bit[row][col];
        
        return sum;
    }
    
    void update(int row, int col, int val) {
        // convert to 1 based index
        ++row, ++col;
        // find the delta change
        int delta = val - nums[row-1][col-1];
        // set the new value
        updateBIT(row, col, delta);
        nums[row-1][col-1] = val;
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        // convert to 1 based indexing
        ++row1, ++col1, ++row2, ++col2;
        
        int total = queryBIT(row2, col2);
        int top_diagonal = queryBIT(row1 - 1, col1 - 1);
        int top_right = queryBIT(row1 - 1, col2);
        int left = queryBIT(row2, col1 - 1);
        
        return total + top_diagonal - top_right - left;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */
