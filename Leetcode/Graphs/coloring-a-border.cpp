/*
    https://leetcode.com/problems/coloring-a-border/
    
    TC: O(MN)
    SC: O(MN)
    
    Idea is to do dfs to traverse and find the connected cells of the component
    housing the source cell. Connected here is one with the same color.
    
*/
class Solution {
private:
    vector<pair<int, int> > directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
public:
    // checks if the coordinates are valid 
    bool isValid(int row, int col, int M, int N) {
        if(row < 0 || row >= M || col < 0 || col >= N)
            return false;
        return true;
    }
    
    void dfs(int row, int col, int color, int comp_color,
             vector<vector<int>>& grid, vector<vector<int>>& colored) {
        // put the color for the current to mark it as visited
        colored[row][col] = grid[row][col];
     
        // check if it is a border element
        for(auto direction: directions) {
            auto [dx, dy] = direction;
            int r = row + dx, c = col + dy;
            
            // Current cell is a border cell if the next neighbor is out of bound or 
            // of different color
            if(!isValid(r, c, grid.size(), grid[0].size()) || grid[r][c] != comp_color) 
                colored[row][col] = color;
            
            // neighbor is connected when it has the same orig color as curr cell,
            // traverse only if not already visited
            if(isValid(r, c, grid.size(), grid[0].size()) &&
               colored[r][c] == -1 && grid[r][c] == comp_color)
                dfs(r, c, color, comp_color, grid, colored);
        }
    }
    
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        if(grid.empty())
            return {};
        
        int M = grid.size(), N = grid[0].size();
        // colored[i][j] = final color of cell
        // Also used for tracking visited cells, -1 indicates unvisited cell
        vector<vector<int>> colored(M, vector<int>(N, -1));
        
        dfs(row, col, color, grid[row][col], grid, colored);    
        
        // fill any -1 cells with orig color
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                if(colored[i][j] == -1)
                    colored[i][j] = grid[i][j];
        
        return colored;
    }
};
