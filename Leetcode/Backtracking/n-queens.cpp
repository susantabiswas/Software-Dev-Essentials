```
/*
    https://leetcode.com/problems/n-queens/
    
    TC: t(n) = nT(n-1) + O(1)
        O(n^n), n calls made at each stage and max depth of n levels, validating correcting pos takes O(1)
    SC: O(n), max stack depth + 3 vectors of multiple * n space
*/
class Solution {
public:
    bool isValid(int row, int col, vector<bool>& visited_cols,
                vector<bool>& upper_left_diagonal, vector<bool>& upper_right_diagonal) {
        // check if any other queen in same col
        if(visited_cols[col])
            return false;
        // check if the upper diagonals have queens placed
        const int N = visited_cols.size();
        if(upper_left_diagonal[col - row + N] || upper_right_diagonal[row + col])
            return false;
        
        return true;
    }
    
    void placeQueens(int row, int n, vector<bool>& visited_cols,
                    vector<string> layout, vector<vector<string>>& result,
                    vector<bool>& upper_left_diagonal, vector<bool>& upper_right_diagonal) {
        // base case, all the n queens have been placed across all the n rows
        if(row == n) {
            result.emplace_back(layout);
            return;
        }
        
        for(int col = 0; col < n; col++) {
            // check if the queen is placed at grid[row][col] position,
            // any other queen can attack or not, basically whether cur pos is valid
            if(isValid(row, col, visited_cols, upper_left_diagonal, upper_right_diagonal)) {
                // place the queen
                layout[row][col] = 'Q';
                visited_cols[col] = true;
                // A queen is placed in the current left and right diagonal directions
                upper_left_diagonal[col - row + n] = true; 
                upper_right_diagonal[row + col] = true;
                
                placeQueens(row+1, n, visited_cols, layout, result, upper_left_diagonal, upper_right_diagonal);
                
                // revert the change
                layout[row][col] = '.';
                visited_cols[col] = false;
                upper_left_diagonal[col - row + n] = false;
                upper_right_diagonal[row + col] = false;
            }
        }
    }
    
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        // visited_cols[c]: whether a queen is placed in c-th column
        vector<bool> visited_cols(n, false);
        
        /*
        We encode the row and col values to map to a single value that can be used to represent
        a diagonal. (row, col) represents 2 diagonals:
        1. \ one which goes to upper left and bottom right
             The coordinates on this diagonal have the same col - row value. We add n so that it stays +ve
        2. / one which goes to upper right and bottom left
             The coordinates on this have the same row + col value. Since this is +ve already and the values 
             increase, we keep it row + col
        */
        // upper_left_diagonal[col - row + n]: whether a queen is placed anywhere along the 
        // upper left diagonal
        vector<bool> upper_left_diagonal(2*n, false);
        // upper_right_diagonal[col + row]: whether a queen is placed anywhere along the 
        // upper right diagonal
        vector<bool> upper_right_diagonal(2*n, false);
        
        // Using the above 3 vectors we can validate a position in O(1)
        placeQueens(0, n, visited_cols, vector<string>(n, string(n, '.')), 
                    result, upper_left_diagonal, upper_right_diagonal);
        return result;
    }
};
```
