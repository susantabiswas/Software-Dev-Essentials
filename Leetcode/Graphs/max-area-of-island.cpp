/*
    https://leetcode.com/problems/max-area-of-island/
    
    Idea is simply keep track of no. of nodes during dfs and pick the max
    nodes out of all connected components.
*/
class Solution {
public:
    int dfs(int i, int j, vector<vector<int>>& grid) {
        // out of bound check
        if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()
          || grid[i][j] == 0)
            return 0;
        // mark as visited
        grid[i][j] = 0;
        // DFS in all 4 directions
        return 1 + dfs(i+1, j, grid) + dfs(i-1, j, grid) + dfs(i, j+1, grid) + dfs(i, j-1, grid);
    }
    
    // TC: O(MN)
    // SC: O(MN)
    int dfsSol(vector<vector<int>>& grid) {
        int max_area = 0;
        
        // Start dfs from all unvisited nodes, each dfs returns the size of
        // connected graph
        for(int i = 0; i < grid.size(); i++)
            for(int j = 0; j < grid[0].size(); j++)
                if(grid[i][j]) {
                    int area = dfs(i, j, grid);
                    max_area = max(max_area, area);
                }
                    
        return max_area;
    }
    
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        return dfsSol(grid);
        // return unionFindSol(grid);
    }
};
