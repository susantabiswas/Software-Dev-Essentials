/*
    https://leetcode.com/problems/shortest-bridge/
    
    TC: O(MN)
    SC: O(M+N)
    
    This is a multi source BFS problem.
    The problem can be thought of as finding the shortest distance to reach any cell
    of island 2 from any cell of island 1.
    
    To optimize things, we do DFS on the first encountered cell with 1 and cover all
    the cells of that island. We color the cells of that island with 2 and keep adding
    the border cells of that island.
    
    Once we have all the border elements of island 1 or 2, then we add them as initial
    sources for BFS. Then perform BFS where we traverse whenever a cell is either 0 or 1 (the other island).
    Once we encounter a cell from the other island, return the distance till there.
    
*/
class Solution {
public:
    vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    bool isValid(int r, int c, vector<vector<int>>& grid) {
         return r >= 0 && r < grid.size() && c >= 0 && c < grid.size();
    }
    
    // Colors all the cells of a connected component
    void dfs(int r, int c, vector<vector<int>>& grid,
            set<pair<int, int>>& border) {
        // color the cell
        grid[r][c] = 2;
        
        for(auto [dx, dy]: dirs) {
            int row = r + dx, col = c + dy;
            
            // current cell is border element of current island
            if(!isValid(row, col, grid) || grid[row][col] == 0) {
                border.insert({r, c});
                continue;
            }
            // only traverse if the next cell is connected
            if(grid[row][col] == 1)
                dfs(row, col, grid, border);
        }
    }
    
    int shortestBridge(vector<vector<int>>& grid) {
        int n_rows = grid.size(), n_cols = grid[0].size();
        
        set<pair<int, int>> border;
        bool colored = false;
        // color one of the islands with color 2
        for(int r = 0; r < n_rows && !colored; r++) 
            for(int c = 0; c < n_cols && !colored; c++)
                if(grid[r][c]) {
                    dfs(r, c, grid, border);
                    colored = true;
                }

        // <row, col, dist>
        queue<array<int, 3>> q;
        // add all the border cells of island with color 2
        for(auto [r, c]: border)
            q.push({r, c, 0});
        
        // find the shortest distance to reach any cell of island with color 1
        while(!q.empty()) {
            auto [row, col, dist] = q.front();
            q.pop();
            
            for(auto [dx, dy]: dirs) {
                int r = row + dx, c = col + dy;
                if(isValid(r, c, grid) && grid[r][c] != 2) {
                    q.push({r, c, dist + 1});
                    
                    if(grid[r][c] == 1)
                        return dist;

                    grid[r][c] = 2;
                }
            }
        }
        return 0;
    }
}; 
