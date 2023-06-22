/*
  https://leetcode.com/problems/search-a-2d-matrix/
*/
class Solution {
public:
    /*
        The matrix is sorted in a special manner i.e
        
        - Each row is sorted in non-decreasing order.
        - The first integer of each row is greater than the last integer of the previous row.
        
        Which means the i+1 row elements are always > i th row elements if laid sequentially.
        So we can imagine the 2D grid as a flattened array which is sorted if the elements are laid out
        row wise.
        
        We can avoid flattening the matrix physically by converting the index from 2D to 1D and vice-versa.
        So treat the 2D grid like a virtual 1D array and use binary search as usual.
    */
    // TC: O(log(MN))
    // SC: O(1)
    // M = no. of rows, N = no. of cols
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n_rows = matrix.size(), n_cols = matrix[0].size();
        int low = 0, high = n_rows * n_cols - 1;
        
        while(low <= high) {
            int mid = low + (high - low) / 2;
            
            // Convert the 1D index to 2D row and col coordinate
            int row = mid / n_cols;
            int col = mid % n_cols;
            
            if(matrix[row][col] == target)
                return true;
            else if(matrix[row][col] < target)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return false;
    }
};
