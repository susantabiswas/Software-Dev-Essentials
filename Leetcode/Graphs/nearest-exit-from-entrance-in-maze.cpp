/*
    https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/
    
    TC: O(MN)
    SC: O(M + N), in the worst case when all the borders are exits. After initial
    addition of sources, we can only add the adj cell which can again not exceed the
    no. of cells in the border.
    
    Idea is to add the exits as the start point and then find the shortest distance
    towards the entrance.
    Since the graph is unweighted we can use BFS to do that.
*/
class Solution {
public:
    bool isValid(int r, int c, int nRows, int nCols) {
        return r >= 0 && r < nRows && c >= 0 && c < nCols;    
    }
    
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        // <row, col, dist>
        queue<array<int, 3>> q;
        
        int nRows = maze.size(), nCols = maze[0].size();
        
        // mark the entrance as not empty so that
        // coding for addition of initial sources become shorter
        maze[entrance[0]][entrance[1]] = 'x';
        
        // add all the exit locations as initial start points
        
        // top and bottom rows
        for(int c = 0; c < nCols; c++) {
            if(maze[0][c] == '.') {
                q.push({0, c, 0});
                maze[0][c] = '+';
            }
            if(maze[nRows - 1][c] == '.') {
                q.push({nRows - 1, c, 0});
                maze[nRows - 1][c] = '+';
            }
        }
        
        // left and right cols
        for(int r = 0; r < nRows; r++) {
            if(maze[r][0] == '.') {
                q.push({r, 0, 0});
                maze[r][0] = '+';
            }
            if(maze[r][nCols - 1] == '.') {
                q.push({r, nCols - 1, 0});
                maze[r][nCols - 1] = '+';
            }
        }
        
        // steps in each direction that can be taken
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
        
        // From the initial start points, find a way to the entrance
        while(!q.empty()) {
            auto [row, col, dist] = q.front();
            q.pop();
            
            if(row == entrance[0] && col == entrance[1])
                return dist;
            
            for(auto [dx, dy]: dirs) {
                int r = row + dx, c = col + dy;
                
                if(isValid(r, c, nRows, nCols) && maze[r][c] != '+') {
                    q.push({r, c, dist + 1});
                    maze[r][c] = '+';
                }
            }
        }
        
        return -1;
    }
};
