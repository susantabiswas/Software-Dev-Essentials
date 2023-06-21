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

/////////////////////////////////// SOLUTION 2: Without Reference Variable
class Solution {
public:
    bool isValid(int r, int c, vector<vector<int>>& grid) {
        return r >= 0 && r < grid.size() &&
            c >= 0 && c < grid[0].size();
    }
    
    // Returns true if the current island is a sub-island
    bool dfs(int r, int c, vector<vector<int>>& grid1,
            vector<vector<int>>& grid2) {
        // out of bound or grid 2's cell has water
        if(!isValid(r, c, grid1) || !grid2[r][c])
            return true;
        
        // Whether the current island is a sub-island or not
        bool sub_island = true;
        
        // land cell in grid 2 but not in grid 1
        // NOTE: We don't prematurely return once there is a violation
        // for sub-island condition. This is because if the current cell
        // makes the entire island not a sub-island then the remaining connected
        // cells of grid 2 should also be marked as visited to indicate that the entire
        // island has finished processing. If we return from here, then the remaining connected
        // land cells will not be traversed in this dfs and will be processed in the driver method later
        // and that might falsely mark the island as a sub-island.
        
        if(grid1[r][c] != grid2[r][c])
            sub_island = false;
        
        // mark grid2's current cell as visited
        grid2[r][c] = 0;
        grid1[r][c] = 0;
        
        // traverse all possible connecting land cells
        // to ensure two things:
        // 1. We traverse the entire island, so that it is not processed later
        // 2. In case of violation of any cell, that is found
        auto down = dfs(r+1, c, grid1, grid2);
        auto up = dfs(r-1, c, grid1, grid2);
        auto right = dfs(r, c+1, grid1, grid2);
        auto left = dfs(r, c-1, grid1, grid2);
        
        return sub_island && up && right && down && left;
    }
    
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int sub_islands = 0;
        
        if(grid2.empty())
            return 0;
        
        int m = grid2.size(), n = grid2[0].size();
        
        for(int r = 0; r < m; r++)
            for(int c = 0; c < n; c++)
                if(grid2[r][c] && dfs(r, c, grid1, grid2)) {
                    ++sub_islands;
                }
        
        return sub_islands;
    }
};
