/*
	https://leetcode.com/problems/leftmost-column-with-at-least-a-one/
    
    For each row we find the first index of 1 if it exists using binary search.
    The answer is the min of all these indices.
    
    TC: O(MlogN), M: num rows, N: num cols
*/

/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int x, int y);
 *     vector<int> dimensions();
 * };
 */

class Solution {
public:
    // Binary search: O(logN)
    int bSearch(BinaryMatrix &binaryMatrix, int target,
                int row, int n) {
        int left = 0, right = n-1;
        
        while(left < right) {
            int mid = left + (right - left) / 2;
            int val = binaryMatrix.get(row, mid);
            
            if(target <= val)
                right = mid;
            else
                left = mid + 1;
        }
        return binaryMatrix.get(row, right) == 0 ? -1 : right;    
    }
    
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        auto dims = binaryMatrix.dimensions();
        int first_col = -1;
        
        for(int i = 0; i < dims[0]; i++) {
            // find the first index of 1
            int idx = bSearch(binaryMatrix, 1, i, dims[1]);
            
            if(idx != -1) {
                if(first_col == -1)
                    first_col = idx;
                else
                    first_col = min(first_col, idx);
            }
        }
        
        return first_col;
    }
};
