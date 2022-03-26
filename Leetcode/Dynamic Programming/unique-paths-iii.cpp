/*
    980. Unique Paths III
    https://leetcode.com/problems/unique-paths-iii/
    We use backtracking for finding the paths. Since movement can be 
    in 4 directions, we form run into a loop path, so we mark each processing node 
    -1 essentially preventing further accessing that cell till we find ways 
    using that cell, after that is done we mark is accessible again.
*/

class Solution {
public:
    void findPaths(pair<int, int>& end, int i, int j, 
                 vector<vector<int>>& grid, int walkable_steps, int& ways) {
        // when target is found and all the walkable points are used
        if(i == end.first && j == end.second) {
            if(walkable_steps == -1)
                ++ways;
            return;
        }
        
        if(i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size())
            return;
        // return if visited or unreacable
        if(grid[i][j] == -1)
            return;
        
        // mark as visited, so that we dont form a loop path
        grid[i][j] = -1;
        
        findPaths(end, i+1, j, grid, walkable_steps-1, ways);
        findPaths(end, i-1, j, grid, walkable_steps-1, ways);
        findPaths(end, i, j+1, grid, walkable_steps-1, ways);
        findPaths(end, i, j-1, grid, walkable_steps-1, ways);

        // mark as unvisited, so that other paths can use this
        grid[i][j] = 0;
    }
    
    int uniquePathsIII(vector<vector<int>>& grid) {
        const int M = grid.size(), N = grid[0].size();
        
        pair<int, int> start = {-1, -1};
        pair<int, int> end = {-1, -1};
        
        // keeps track of total number of cells that are walkable
        int walkable_steps = 0;
        // find the coordinates of start, finish point and total walkable steps 
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++) {
                if(grid[i][j] == 1) {
                    start.first = i;
                    start.second = j;
                }
                else if(grid[i][j] == 2) {
                    end.first = i;
                    end.second = j;
                }
                else if(grid[i][j] == 0)
                    ++walkable_steps;
            }
        
        // if no start or end found
        if(start.first == -1 || start.second == -1 || end.first == -1 || end.second == -1)
            return 0;
        int ways = 0;
        findPaths(end, start.first, start.second, grid, walkable_steps, ways);
        
        return ways;
    }
};
