/*
    https://leetcode.com/problems/number-of-closed-islands/
    
    The problem asks us to find the land cells not cut off from the boundary.
    This is only possible if the land is an island surrounded by water from all sides,
    but finding an island surrounded by water is very difficult problem. Istead we can 
    can rule the land cells that have access to out of boundary. The land cells which have a path
    connecting to the boundary can only have access. In other words, the land cells on the boundary 
    will be part of these paths, so we traverse from border land cells and mark all the land cells 
    they connect to, whatever is left after this are islands.
    
    TC: O(MN)
    SC: O(1)
*/
class Solution {
public:
    void dfs(int row, int col, vector<vector<int>>& grid) {
        // out of bound or water cell
        if(row < 0 || row >= grid.size() || col < 0 ||
            col >= grid[0].size() || grid[row][col] == 1)
            return;

        // mark as visited by changing land to sea
        grid[row][col] = 1;
        
        dfs(row + 1, col, grid);
        dfs(row - 1, col, grid);
        dfs(row, col + 1, grid);
        dfs(row, col - 1, grid);    
    }

    int closedIsland(vector<vector<int>>& grid) {
        if(grid.empty())
            return 0;

        int M = grid.size(), N = grid[0].size();

        // Traverse the land cells connected to border
        // These cannot be surrounded by ocean water
        for(int r = 0; r < M; r++)
            for(int c = 0; c < N; c++)
                // Either top, bottom, left or right border node
                if((r == 0 || r == M - 1 || c == 0 || c == N - 1) &&
                    grid[r][c] == 0)
                        dfs(r, c, grid);

        // Check for connected land cells making an island 
        int islands = 0;
        for(int r = 0; r < M; r++)
            for(int c = 0; c < N; c++)
                if(grid[r][c] == 0) {
                    ++islands;
                    dfs(r, c, grid);
                }
        return islands;
    }
};


