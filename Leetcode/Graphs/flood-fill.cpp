/*
    https://leetcode.com/problems/flood-fill/submissions/
    
    This can be mapped to a graph traversal problem, each valid adjacent vertex
    is the pixel value that is adjacent neighbor of current pixel position and 
    of the same color as that of source vertex.
    
    TC: O(MN)
*/
/////////////////////////////////////////////////////////// No extra visited array
class Solution {
public:
    void dfs(int row, int col, vector<vector<int>>& grid, int orig_color, int new_color) {
        // base check
        if(!(row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size() &&
          grid[row][col] == orig_color))
            return;
        
        grid[row][col] = new_color;
        
        dfs(row+1, col, grid, orig_color, new_color);
        dfs(row-1, col, grid, orig_color, new_color);
        dfs(row, col+1, grid, orig_color, new_color);
        dfs(row, col-1, grid, orig_color, new_color);
    }
    
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int orig_color = image[sr][sc];

        // only makes sense to iterate the neighbors and start pt if the color is different
        if(orig_color != color)
            dfs(sr, sc, image, orig_color, color);
        return image;
    }
};

/////////////////////////////////////////////////////////// with visited array
class Solution {
public:
    // For doing DFS
    void dfs(int i, int j, int src_color,
             int& new_color, vector<vector<int>>& grid,
            vector<vector<bool>>& visited) {
       
        // out of boundary checking and if the color of current is diff 
        // than that of source pixel and if iit is already visited, then return
        if(i < 0 || i >= grid.size() || j < 0 ||
          j >= grid[0].size())
            return;
        
        if(grid[i][j] != src_color || visited[i][j])
            return;
        
        // mark it visited
        visited[i][j] = true;
        // change the color of pixel
        grid[i][j] = new_color;
        // traverse in 4 directions to all the reachable pixels
        dfs(i, j-1, src_color, new_color, grid, visited);
        dfs(i, j+1, src_color, new_color, grid, visited);
        dfs(i-1, j, src_color, new_color, grid, visited);
        dfs(i+1, j, src_color, new_color, grid, visited);
    }
    
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if(image.empty())
            return vector<vector<int>>{};
        
        // for keeping track of visited positions
        vector<vector<bool>> visited(image.size(), vector<bool>(image[0].size(), false));
        dfs(sr, sc, image[sr][sc], newColor, image, visited);
        return image;
    }
};
