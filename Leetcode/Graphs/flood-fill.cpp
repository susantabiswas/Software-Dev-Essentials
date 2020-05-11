/*
    https://leetcode.com/problems/flood-fill/submissions/
    
    This can be mapped to a graph traversal problem, each valid adjacent vertex
    is the pixel value that is adjacent neighbor of current pixel position and 
    of the same color as that of source vertex.
    
    TC: O(MN)
*/
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
