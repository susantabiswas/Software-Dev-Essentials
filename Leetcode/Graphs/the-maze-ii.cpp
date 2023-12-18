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
    
    // TC: O((MN)log(MN) + MN * max(M, N)), (Heap operations + For each cell, we traverse in 4 dirs till a wall is hit)
    // SC: O(MN)
    // OPTIMIZATION: We can use a distance matrix which tracks the min distance for each cell from the start. 
    // We only add the edge which gives a better distance value for that neighbor
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

//////////////////////////////////// BFS Solution
class Solution {
public:
    // TC: O(MN * min(M, N))
    // Each node can only be visited via a path once, so at max a node will be
    // visited via 3 directions at max (there will be atleast 1 side with a wall which made the ball stationary).
    // If an already visited path is visited again, it will only increase the distance from source and wont 
    // be added to queue.
    // SC: O(MN)
    
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        vector<array<int, 2>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int m = maze.size(), n = maze[0].size();
        
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        // <row, col>
        queue<array<int, 2>> q;
        
        // add the start pt and set its dist=0
        q.push({start[0], start[1]});
        dist[start[0]][start[1]] = 0;
        
        // Explore all the edges that can give potential paths
        // Unlike dijikstra, here the elements are not picked based on any cost
        // metric, so imp to traverse till we can.
        // Since the  
        while(!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            // explore the neighbors
            for(auto [dx, dy]: dirs) {
                int r = row, r_next = row + dx;
                int c = col, c_next = col + dy;
                
                // move till not hit by a wall
                while(r_next >= 0 && r_next < m && c_next >= 0 && c_next < n && maze[r_next][c_next] != 1) {
                    r = r_next;
                    c = c_next;
                    
                    r_next += dx, c_next += dy;
                }
                
                int d = abs(r - row) + abs(c - col) + dist[row][col];
                
                if((r != row || c != col) && dist[r][c] > d) {
                    dist[r][c] = d;
                    q.push({r, c});
                }
            }
        }   
        
        return dist[destination[0]][destination[1]] == INT_MAX ? -1 : dist[destination[0]][destination[1]];
    }
};
