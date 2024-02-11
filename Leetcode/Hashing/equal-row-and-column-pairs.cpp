/*
    https://leetcode.com/problems/equal-row-and-column-pairs/
    
    TC: O(n^2)
    SC: O(n^2)
    
    Idea is to hash and save the col hashes with their frequency in a hash table.
    Then we find the hash for each row and check the frequency of that hashed row if that
    exists as column.
*/
class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        unordered_map<string, int> cols;
        
        int n = grid.size();
        
        // hash the cols and track in hash table
        for(int c = 0; c < n; c++) {
            string col;
            
            for(int r = 0; r < n; r++)
                col += to_string(grid[r][c]) + ",";
            
            ++cols[col];
        }
        
        // for each row, check if its hash is present as a cols or not
        int same = 0;
        
        for(int r = 0; r < n; r++) {
            string row;
            
            for(int c = 0; c < n; c++)
                row += to_string(grid[r][c]) + ",";
            
            same += cols[row];
        }
        return same;
    }
};
