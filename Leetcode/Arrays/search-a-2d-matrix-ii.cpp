/*
    https://leetcode.com/problems/search-a-2d-matrix-ii/submissions/
    
    Since the rows and cols are ordered, we can start with the smallest element of largest row 
    of elements. If the current element is greater than current, we check in the previous row.
    If it is smaller, we check it with the elements of the current row.
    TC: O(M + N)
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty())
            return false;
        const int M = matrix.size(), N = matrix[0].size();
        int row = M-1, col = 0;
        
        while(row >= 0 && col < N) {
            if(matrix[row][col] == target)
                return true;
            else if(matrix[row][col] > target)
                --row;
            else
                ++col;
        }
        return false;
    }
};
