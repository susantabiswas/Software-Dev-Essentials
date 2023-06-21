/*
    https://leetcode.com/problems/count-sub-islands/
    
    Idea is to perform normal DFS for the 2nd grid by chaining the 
    land cells. If at any instance, the cell in grid1 is not land when it
    is land in grid2, then that island is not a sub island.
    
    TC: O(MN)
    SC: O(MN)
*/

class Solution {
public:
    
    // SOLUTION 1: USING REFERENCE VARIABLE
    bool isValid(int r, int c, vector<vector<int>>& grid) {
        return r >= 0 && r < grid.size() &&
            c >= 0 && c < grid[0].size();
    }
    
    void dfs(int row, int col, vector<vector<int>>& grid1, vector<vector<int>>& grid2,
            bool& sub_island) {
        // invalid position or if grid2's cell is not land
        if(!isValid(row, col, grid1) || !grid2[row][col])
            return;
    
        // If grid2 has land then grid1 should also have land cell
        // otherwise current island is not a sub island
        if(grid1[row][col] != grid2[row][col]) {
            // We don't return from here because the entire connected island
            // is not a sub-island, so it is better to traverse the remaining connected
            // land cells and mark them as visited and the sub_island is already set as false
            sub_island = false;
        }
        
        // both the grids have the current cell as land (1)
        // mark them visited by unsetting the cell
        grid1[row][col] = 0;
        grid2[row][col] = 0;
        
        dfs(row + 1, col, grid1, grid2, sub_island);
        dfs(row - 1, col, grid1, grid2, sub_island);
        dfs(row, col + 1, grid1, grid2, sub_island);
        dfs(row, col - 1, grid1, grid2, sub_island);
    }
    
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        if(grid1.empty())
            return 0;
        
        int sub_islands = 0;
        int m = grid1.size(), n = grid1[0].size();
        
        for(int r = 0; r < m; r++)
            for(int c = 0; c < n; c++) {
                // Whether sub island exists
                bool sub_island = true;
                
                if(grid2[r][c]) {
                    // The dfs will traverse the entire connected island of grid2
                    // even if at some point we find that it is not a sub-island. This
                    // ensures that we don't process any part of that island later here.
                    dfs(r, c, grid1, grid2, sub_island);
                    if(sub_island)
                        ++sub_islands;
                }
            }
        
        return sub_islands;
    }
};
