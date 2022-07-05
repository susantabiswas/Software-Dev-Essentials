/*
    https://leetcode.com/problems/number-of-distinct-islands/
    
    TC: O(MN)
    SC: O(MN)
    
    There are 2 steps involved:
    1. Finding the discconnected islands - Can be solved by DFS/BFS/Union-Find
    2. Finding the shape of an island and having a way to compare two given shapes.
    
    For #1, we use DFS traversal and sol(..) has the code that finds different islands using dfs.
    
    Now for #2, we have 2 ideas:
    We can use the traversal data to serialize the shape of an island, for this we can do it 2 ways:
    
    1. Store the coordinates of each cell during the traversal and then save it in a hash table. For finding 
    if a similarly shaped island is present, we check the traversal pattern in the hash table.
    Now the issue with saving the coordinates is that they will be relative to (0, 0) and hence even though we have 
    similar shapes, the set of coordinates will be different.
    To mitigate this, we need to align the start of the island which is [row][col] with some reference point.
    We can move the start cell of an island to top left position, this would mean for a start cell = [2,3],
    it would be moved 2 steps up and 3 steps right. All the cells in the island will also be moved by [2,3] in a 
    similar manner. 
    To move an island to top left, we can take the start cell's coordinates as the offset distance for row and column.
    Subtract this from each cell and we will have everything aligned to top left. Then save the coordinates.
    
    2. Other option is to save the direction of traversal during DFS. We use the following symbols:
    S = start, B = Backtrack, U = Up, D = Down, R = Right, L = Left.
    Each time we take a step during DFS, pass the appropriate direcyion alongside. Now the reason we have B as a dircetion is because
    with just the 4 directions, diff shapes might give the same traversal order.
    S                      
    |
    D
    |
    D-R
    |
    D
    
    S
    |
    D
    |
    D
    |
    D-R
    
    Both the shapes will give SDDDR without B.
    With B, shape 1: SDDDBRBBBB, shape 2: SDDDRBBBBB
*/
class Solution {
public:
    void dfs(int row, int col, vector<vector<int>>& grid,
            string& traversal, int row_offset, int col_offset) {
        // otu of bound or already visited or a 0 cell
        if(row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size()
          || !grid[row][col])
            return;
        
        // mark as visited
        grid[row][col] = 0;
        // add the cell coordinates to traversal. We standarize the coordinates by bringing it to 
        // to common reference. In this case, the start node is put to the top left cell i.e (0, 0)
        // and all the cells of the islands are offset and moved to left and up by (row, col) of start node
        int r = row - row_offset, c = col - col_offset;
        traversal.append("(" + to_string(r) + "," + to_string(c) + ")");
        // traverse the other dirs
        dfs(row + 1, col, grid, traversal, row_offset, col_offset);
        dfs(row - 1, col, grid, traversal, row_offset, col_offset);
        dfs(row, col + 1, grid, traversal, row_offset, col_offset);
        dfs(row, col - 1, grid, traversal, row_offset, col_offset);
    }
    
    void dfsWithDirection(int row, int col, vector<vector<int>>& grid,
                        string& traversal, char direction) {
        // otu of bound or already visited or a 0 cell
        if(row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size()
          || !grid[row][col])
            return;
        
        // mark as visited
        grid[row][col] = 0;
        traversal += direction;
        // traverse the other dirs
        dfsWithDirection(row + 1, col, grid, traversal, 'D');
        dfsWithDirection(row - 1, col, grid, traversal, 'U');
        dfsWithDirection(row, col + 1, grid, traversal, 'R');
        dfsWithDirection(row, col - 1, grid, traversal, 'L');
        // Marks retracking, this is important otherwise different shapes can have the same traversal
        traversal += 'B';
    }
    
    int sol(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int unique_islands = 0;
        // Set of traversed island coordinates 
        unordered_set<string> islands;
        
        for(int row = 0; row < m; row++)
            for(int col = 0; col < n; col++)
                // unvisited island
                if(grid[row][col]) {
                    // saves the traversal 
                    string traversal;
                    // SOLUTION DFS 1: Saves the coordinates traversed
                    // dfs(row, col, grid, traversal, row, col);
                    
                    // SOLUTION DFS 2: Saves the direction of each traversal step
                    dfsWithDirection(row, col, grid, traversal, 'S');
                    
                    // check if the island id unique by matching against the other islands
                    if(!islands.count(traversal))
                        ++unique_islands;
                    islands.emplace(traversal);
                }
        return unique_islands;
    }
    
    int numDistinctIslands(vector<vector<int>>& grid) {
        return sol(grid);
    }
};
