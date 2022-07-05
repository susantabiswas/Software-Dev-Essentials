/*
    https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/
    
    
    Solution 1: BFS
    Simple BFS from source to destination and keeping track of visited cells. Only addition is the option
    to remove obstacles, so for our state we can have = {row, col, num_obstacles_can_be_removed}.
    We save this info as part of visited state.
    
    Solution 2: A* Algorithm
    
    Very similar to normal BFS with the difference that it is based on a cost function and tries to give priority to
    the move with the least/max cost. The cost function will be different for each problem and should be something that can correctly
    estimate the effort towards the goal.
    
    Here goal is to reach the destination in min no. of steps, so for cost function we can use manhattan distance.
    
    It is based on f(n) = g(n) + h(n)
    g(n): The cost to reach the step cell from the start.
    h(n): Heuristic estimation on the cost to reach the destination from the current cell. 
    f(n): Estimated total cost to reach the destination if one starts from current cell.
    
    The code pretty much stays the same as that of BFS with minor changes.
    We replace normal queue with a heap, min heap in this case.
    Compute a cost field to the input data that the heap can use for select the top element.
    
*/

class Solution {
private:
    // down, right, up, left
    vector<pair<int, int> > directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
public:
    bool isValid(int row, int col, int m, int n) {
        return row >= 0 && row < m && col >= 0 && col < n;    
    }
    
    /////////////////////////// SOLUTION 1: BFS
    // TC: O(MN * K)
    // SC: O(MN * K), Each cell is visited once with at max each cmb of K
    int bfsSol(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        // <"row,col,obstacles_remaining">
        unordered_set<string> visited;
        // <row, col, obstacles_remaining, steps_taken>
        queue<array<int, 4> > q;
        
        q.push({0, 0, k, 0});
        visited.emplace(to_string(0) + "," + to_string(0) + "," + to_string(k));
        
        while(!q.empty()) {
            auto [r, c, obstacles, steps] = q.front();
            q.pop();
            
            // target found
            if(r == m-1 && c == n-1)
                return steps;
            
            // explore unvisited neighbors
            for(auto [dx, dy]: directions) {
                int row = dx + r, col = dy + c;
                string hash_key = to_string(row) + "," + to_string(col) + "," + to_string(obstacles);
                
                if(isValid(row, col, m, n) && !visited.count(hash_key) && (grid[row][col] == 0 || (grid[row][col] == 1 && obstacles > 0))) {
                    if(grid[row][col] == 0) {
                        q.push({row, col, obstacles, steps + 1});
                        visited.emplace(hash_key);
                    }
                    // Going via an obstacle
                    else {
                        q.push({row, col, obstacles - 1, steps + 1});
                        visited.emplace(hash_key);
                    }
                }
            }
        }
        return -1;
    }
    
    int manhattanDistance(int r1, int c1, int r2, int c2) {
        return abs(r1 - r2) + abs(c1 - c2);
    }
    
    //////////////////////// SOLUTION 2: A*
    // TC: O(M.N.Klog(M.N.K))
    // SC: O(M.N.K), Each cell is visited once with at max each cmb of K
    int aStarSol(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        // <"row,col,obstacles_remaining">
        unordered_set<string> visited;
        
        // Based on f(n) = g(n) + h(n)
        // g(n): The cost to reach the step cell from the start.
        // h(n): Heuristic estimation on the cost to reach the destination from the current cell. 
        // f(n): Estimated total cost to reach the destination if one starts from current cell.
        auto comp = [&](const array<int, 5>& a, const array<int, 5>& b) { return (a[3] + a[4]) > (b[3] + b[4]); };
        // <row, col, obstacles_remaining, steps_taken, manhattan_distance_till_destination>
        // The min heap picks the cell based on the cost function of A*
        priority_queue<array<int, 5>, vector<array<int, 5> >, decltype(comp) > q(comp);
        
        q.push({0, 0, k, 0, manhattanDistance(0, 0, m-1, n-1)});
        visited.emplace(to_string(0) + "," + to_string(0) + "," + to_string(k));
        
        while(!q.empty()) {
            auto [r, c, obstacles, steps, dist_left] = q.top();
            q.pop();
            
            // target found
            if(r == m-1 && c == n-1)
                return steps;
            
            // explore unvisited neighbors
            for(auto [dx, dy]: directions) {
                int row = dx + r, col = dy + c;
                string hash_key = to_string(row) + "," + to_string(col) + "," + to_string(obstacles);
                // Compute the cost function for A*, f(n) = g(n) + h(n)
                int dist_left_next = (steps + 1) + (manhattanDistance(row, col, m-1, n-1));
                    
                if(isValid(row, col, m, n) && !visited.count(hash_key) && (grid[row][col] == 0 || (grid[row][col] == 1 && obstacles > 0))) {
                    if(grid[row][col] == 0) {
                        q.push({row, col, obstacles, steps + 1, dist_left_next});
                        visited.emplace(hash_key);
                    }
                    // Going via an obstacle
                    else {
                        q.push({row, col, obstacles - 1, steps + 1, dist_left_next});
                        visited.emplace(hash_key);
                    }
                }
            }
        }
        return -1;
    }
    
    int shortestPath(vector<vector<int>>& grid, int k) {
        // return bfsSol(grid, k);
        return aStarSol(grid, k);
    }
};
