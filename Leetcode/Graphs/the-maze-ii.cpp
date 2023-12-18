/*
    https://leetcode.com/problems/the-maze-ii/
    
    Since this is a shortest distance problem we can use Djikstra or BFS. There is a caveat with using BFS
    though. BFS is suitable for shortest distance when all the directions have the same magnitude of change,
    eg in normal unweighted graph, each direction has a magnitude of 1.
    Here we might be able to traverse diff amount of distance in each direction due to the walls and hence 
    normal way of using BFS might not work. Djikstra will work just fine.
    
    To use BFS here we need to do something similar to Bellman-Ford's relaxation, meaning we keep don't use a 
    visited set to mark the visited places. This is because there be a path that comes on later with a smaller
    distance. So we keep iterating till we see the target for the 1st time.
    
    For this solution, I have used Djikstra as it is naturally suited for these scenarios of unequal weights.
*/
class Solution {
private:
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
public:
    // Whether cell coords are valid
    bool isValid(int row, int col, int m, int n, vector<vector<int>>& maze) {
        return row >= 0 and row < m and col >= 0 and col < n and maze[row][col] == 0;
    }
    
    // TC: O((MN)log(MN))
    // SC: O(MN)
    int djikstra(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int m = maze.size(), n = maze[0].size();
        
        // Min heap based on the distance traversed so far
        auto comp = [&](const array<int, 3>& a, const array<int, 3>& b) { return a[0] > b[0]; };
        priority_queue<array<int, 3>, vector<array<int, 3>>, decltype(comp)> min_heap(comp);
        // <steps, row, col>
        min_heap.push({0, start[0], start[1]});
        
        // for tracking visited cells
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        while(!min_heap.empty()) {
            auto [dist, r, c] = min_heap.top();
            min_heap.pop();
            
            if(visited[r][c])
                continue;
            
            // mark as visited
            visited[r][c] = true;
            
            // target reached
            if(r == destination[0] && c == destination[1])
                return dist;
            
            // visit the start points reachable from current start position
            for(auto [dx, dy]: directions) {
                int row = r + dx, col = c + dy;
                int steps = 0;
                // move until a wall is hit and also keep track of steps taken
                while(isValid(row, col, m, n, maze))
                    row += dx, col += dy, steps += 1;
                // Since a wall is hit, take a step back
                row -= dx, col -= dy;
                // if the next start point is not visited, queue it
                if(!visited[row][col]) 
                    min_heap.push({dist + steps, row, col});
            }
        }
        return -1;
    }
    
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        return djikstra(maze, start, destination);
    }
};
