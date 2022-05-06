/*
    https://leetcode.com/problems/path-with-minimum-effort/
    
    Sol1 : Binary Search + DFS
        Idea is to think of finding the min effort in the possible effort search space
        using binary search. For each effort, we check if it is possible to reach the target
        from source with effort not exceeding the effort limit. If optimal cost is C, then 
        C+1, C+1 ..... cost will also be true and C-1,C-2... will be false. Hence we can look
        for the optimal value using binary search.
        
    Sol2: Djikstra modified
        Very similar to normal djikstra, we just change the cost def of path.
*/
class Solution {
public:
    // Checks if it is possible to reach destination with max given cost value
    bool dfs(int row, int col, int limit, int prev,
             vector<vector<int>>& heights, vector<vector<bool>>& visited) {
        // base case: check any of the conditions are violated
        if(row < 0 || row >= heights.size() || col < 0 || col >= heights[0].size()
          || visited[row][col] || abs(heights[row][col] - prev) > limit)
            return false;
        // mark curr as visited
        visited[row][col] = true;
        // target reached
        if(row == heights.size()-1 && col == heights[0].size()-1)
            return true;
        
        return dfs(row, col+1, limit, heights[row][col], heights, visited)
            || dfs(row, col-1, limit, heights[row][col], heights, visited)
            || dfs(row+1, col, limit, heights[row][col], heights, visited)
            || dfs(row-1, col, limit, heights[row][col], heights, visited);
    }
    
    // Solution 1: Using Binary Search + DFS
    // TC: O(MN * log(INT_MAX))
    // SC: O(MN), for visited matrix
    int binSearchSol(vector<vector<int>>& heights) {
        const int M = heights.size(), N = heights[0].size();
        // Find the max and min heights so that we can 
        // get max and min limits of our search space
        int upper = INT_MAX, lower = 0;
        // Keep searching for the min permissible path cost to reach target
        while(lower < upper) {
            vector<vector<bool>> visited(M, vector<bool>(N, false));
            
            int mid = lower + (upper - lower) / 2;
            // the higher cost effort is possible so next look for a smaller effort cost
            if(dfs(0, 0, mid, heights[0][0], heights, visited))
                upper = mid;
            else
                lower = mid + 1;
        }
        return upper;
    }
    
    // Solution 2: Using variation of shortest path djikstra
    // TC: O(MNlog(MN))
    // SC: O(MN)
    int djikstraSol(vector<vector<int>>& heights) {
        const int M = heights.size(), N = heights[0].size();
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        // effort[r][c] = min effort to reach pos r and c
        vector<vector<int>> effort(M, vector<int>(N, INT_MAX));
        
        // custom comparator for min heap of vector elements
        auto comp = [&](const array<int, 3>& a, const array<int, 3>& b) { return a[0] >= b[0]; };
        
        priority_queue<array<int, 3>, vector<array<int, 3>>, decltype(comp)> min_heap(comp);
        
        // starting source will have 0 effort
        effort[0][0] = 0;
        min_heap.push({0, 0, 0});
        
        while(!min_heap.empty()) {
            auto[curr_effort, row, col] = min_heap.top();
            min_heap.pop();
            
            // if target reached
            if(row == M-1 && col == N-1)
                break;
            
            // for the current position we might get an already traversed path
            // leading to this, but the effort for that won't be lesser
            if(curr_effort > effort[row][col]) continue;
                
            for(auto dir: directions) {
                // since the cost is monotonically increasing, there is no point 
                // traversing up and left as even if they can find a smaller cost,
                // still the max cost seen uptil that point will be the effort
                int r = row + dir[0], c = col + dir[1];
                // check for any violations
                if(r >= 0 && r < M && c >= 0 && c < N) {
                    int new_effort = max(curr_effort, abs(heights[row][col] - heights[r][c]));
                    if(new_effort < effort[r][c]) {
                        effort[r][c] = new_effort;
                        min_heap.push({effort[r][c], r, c});
                    }
                }
            }
        }
        
        return effort[M-1][N-1];    
    }
    
    int minimumEffortPath(vector<vector<int>>& heights) {
        // return binSearchSol(heights);
        return djikstraSol(heights);
    }
};
