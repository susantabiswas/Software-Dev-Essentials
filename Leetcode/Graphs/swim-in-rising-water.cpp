/*
    https://leetcode.com/problems/swim-in-rising-water/
    
    Sol1 : Binary Search + DFS
        Idea is to think of finding the min time in the possible effort search space
        using binary search. For each time, we check if it is possible to reach the target
        from source with effort not exceeding the time limit. If optimal cost is C, then 
        C+1, C+1 ..... cost will also be true and C-1,C-2... will be false. Hence we can look
        for the optimal value using binary search.
        
    Sol2: Djikstra modified
        Very similar to normal djikstra, we just change the cost def of path.
*/
class Solution {
public:
    
    bool dfs(int row, int col, int t,
             vector<vector<int>>& grid, vector<vector<bool>>& visited) {
        // base case: check any of the conditions are violated
        if(row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size()
          || visited[row][col] || grid[row][col] > t)
            return false;
        
        visited[row][col] = true;
        
        if(row == grid.size()-1 && col == grid[0].size()-1)
            return true;
        
        return dfs(row+1, col, t, grid, visited)
            || dfs(row-1, col, t, grid, visited)
            || dfs(row, col+1, t, grid, visited)
            || dfs(row, col-1, t, grid, visited);
    }
    
    // TC: O(MN log INT_MAX)
    // SC: O(MN)
    int binSearchSol(vector<vector<int>>& grid) {
        const int M = grid.size(), N = grid[0].size();
        // Find the max and min heights so that we can 
        // get max and min limits of our search space
        int upper = INT_MAX, lower = 0;
        
        while(lower < upper) {
            int mid = lower + (upper - lower) / 2;
            vector<vector<bool>> visited(M, vector<bool>(N, false));
            // the higher cost effort is possible so next look for a smaller effort cost
            if(dfs(0, 0, mid, grid, visited))
                upper = mid;
            else
                lower = mid + 1;
        }
        return upper;
    }
    
    // TC: O(MNlog(MN))
    // SC: O(MN)
    int djikstraSol(vector<vector<int>>& grid) {
        const int M = grid.size(), N = grid[0].size();
        vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        // least_time[r][c] = min time at which curr pos can be reached
        vector<vector<int>> least_time(M, vector<int>(N, INT_MAX));
        
        auto comp = [&](const array<int, 3>& a, const array<int, 3>& b) { return a[0] >= b[0]; };
        priority_queue<array<int, 3>, vector<array<int, 3>>, decltype(comp)> min_heap(comp);    
        // grid[0][0] is the min time to start travelling
        min_heap.push({grid[0][0], 0, 0}); // time, row, col
        
        while(!min_heap.empty()) {
            auto[curr_time, row, col] = min_heap.top();
            min_heap.pop();
            
            // if curr path is not lesser, no point exploring since
            // we have a monotonically increasing cost function
            if(least_time[row][col] < curr_time) 
                continue;
            // target reached
            if(row == M-1 && col == N-1)
                return curr_time;
            // traverse all the neighbours, pick the paths that can
            // lead to a shorter time path
            for(auto dir: directions) {
                int r = row + dir[0], c = col + dir[1];
                if(r >= 0 && r < M && c >= 0 && c < N) {
                    
                    int new_time = max(curr_time, grid[r][c]);
                    if(new_time < least_time[r][c]) {
                        min_heap.push({new_time, r, c});
                        least_time[r][c] = new_time;
                    }
                }
            }
        }
        
        return 0;
    }
    
    int swimInWater(vector<vector<int>>& grid) {
        // return binSearchSol(grid);
        return djikstraSol(grid);
    }
};
