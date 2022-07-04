/*
    https://leetcode.com/problems/the-maze/
    
    This problem is different from normal DFS in the sense that we can't stay at rest
    at each cell unless there is a nearby wall.
    A point can only be rest when it hits a wall in the direction of movement. It is also the
    only point where it can change the direction.
    We can do traversal like normal DFS or BFS with the caveat that we only add the points at rest
    during traversal. For a point at rest we move in all 4 directions and find the point at rest for the directions 
    and put these as the next set of traversal points for next iteration.
    
    Using this logic there are two ways:
    SOLUTION 1. DFS
    SOLUTION 2. BFS
    TC: O(MN)
    SC: O(MN)
*/
class Solution {
private:
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
public:
    
    // Out of bound check + Empty cell
    bool isValid(int row, int col, int m, int n, vector<vector<int>>& maze) {
        return row >= 0 && row < m && col >= 0 && col < n && maze[row][col] == 0;
    }
    
    // SOLUTION 1: DFS
    // TC: O(MN)
    // SC: O(MN)
    bool dfs(vector<int> start, vector<vector<int>>& maze, vector<vector<bool>>& visited,
            vector<int>& dst) {
        // out of bound or already visited or a wall
        if(!isValid(start[0], start[1], maze.size(), maze[0].size(), maze) ||
           visited[start[0]][start[1]])
            return false;
        
        // mark as visited
        visited[start[0]][start[1]] = true;
        
        // target reached, since the start point is always a point at rest
        if(start == dst)
            return true;
        
        for(auto [dx, dy]: directions) {
            int row = start[0] + dx, col = start[1] + dy;
            // Move till we don't hit a wall
            while(isValid(row, col, maze.size(), maze[0].size(), maze))
                row += dx, col += dy;
            // Now that a wall has been hit, retrack a step back to get to an empty cell
            row -= dx, col -= dy;
            // Now we are at a cell in a stopped state i.e not moving. We can change the direction from here
            if(dfs({row, col}, maze, visited, dst))
                return true;
        }
        return false;
    }
    
    // SOLUTION 2: BFS
    // TC: O(MN)
    // SC: O(MN)
    bool bfs(vector<int> start, vector<vector<int>>& maze, vector<vector<bool>>& visited,
            vector<int>& dst) {
        queue<vector<int>> q;
        q.emplace(start);
        
        while(!q.empty()) {
            auto start = q.front();
            q.pop();
            
            // mark the current start point as visited
            visited[start[0]][start[1]] = true;
            
            // target reached
            if(start == dst)
                return true;
            // From the current start point, explore moving in all 4 directions
            for(auto [dx, dy]: directions) {
                int row = start[0] + dx, col = start[1] + dy;
                // Move till we don't hit a wall
                while(isValid(row, col, maze.size(), maze[0].size(), maze))
                    row += dx, col += dy;
                // Now that a wall has been hit, retrack a step back to get to an empty cell
                row -= dx, col -= dy;
                // Now we are at a cell in a stopped state i.e not moving. We can change the direction from here
                if(!visited[row][col])
                    q.emplace(vector<int>{row, col});
            }
        }
        return false;
    }
    
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int m = maze.size(), n = maze[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
    
        // return dfs(start, maze, visited, destination);
        return bfs(start, maze, visited, destination);
    }
};
