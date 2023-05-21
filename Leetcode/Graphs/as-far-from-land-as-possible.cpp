/*
    https://leetcode.com/problems/as-far-from-land-as-possible/
    
    The core idea is to find the shortest distance of each water cell from
    the nearest land cell, then track the max distance encountered.
    Now how to find the shortest distance of water cell from nearest land cell?
    
    We can use a shortest path algorith, treat all the land cells as the initial sources.
    From there we find the shortest distance of their neighboring water cells.
    Since there is no weight/cost between the cells, we can also use BFS for finding the
    shortest distance.
    
    Solution 1: BFS
    Solution 2: Djikstra
*/
class Solution {
public:
    // Solution 1: BFS
    // TC: O(MN)
    // SC: O(MN)
    int bfsSol(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();
        vector<vector<bool>> visited(M, vector<bool>(N, false));
        
        queue<array<int, 3> > q;
        
        // Add all the land coordinates as source points
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                if(grid[i][j] == 1) {
                    q.push({0, i, j});
                }

        int max_dist = -1;

        vector<pair<int, int> > directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        
        while(!q.empty()) {
            auto [dist, row, col] = q.front();
            q.pop();
            
            if(visited[row][col])
                continue;
            
            visited[row][col] = true;
            
            // if the cell is of water
            if(grid[row][col] == 0)
                max_dist = max(max_dist, dist);

            for(auto direction: directions) {
                auto [dx, dy] = direction;
                int r = row + dx, c = col + dy;
                
                // only add the neighbor if it's water
                if(r >= 0 && r < M && c >= 0 && c < N && 
                   grid[r][c] == 0) {
                    
                    q.push({dist + 1, r, c});
                }
            }
        }

        return max_dist;
    }
    
    // Solution 2: Djikstra
    // TC: O(MNlog(MN))
    // SC: O(MN)
    int djikstraSol(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();

        auto comp = [&](const array<int, 3>& a, const array<int, 3>& b) { return a[0] > b[0]; };
        priority_queue<array<int, 3>, vector<array<int, 3> >, decltype(comp)> min_heap(comp);
        
        vector<vector<int>> distance(M, vector<int>(N, INT_MAX));
        
        // Add all the land coordinates as source points
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                if(grid[i][j] == 1) {
                    distance[i][j] = 0;
                    min_heap.push({0, i, j});
                }

        int max_dist = -1;

        vector<pair<int, int> > directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        
        while(!min_heap.empty()) {
            auto [dist, row, col] = min_heap.top();
            min_heap.pop();
            
            // outdated distance value for the cell, skip it
            if(distance[row][col] < dist)
                continue;

            // if the cell is of water
            if(grid[row][col] == 0)
                max_dist = max(max_dist, dist);

            for(auto direction: directions) {
                auto [dx, dy] = direction;
                int r = row + dx, c = col + dy;
                
                // only add the neighbor if it's water and it's
                // new distance is smaller
                if(r >= 0 && r < M && c >= 0 && c < N && 
                   grid[r][c] == 0 && distance[r][c] > dist + 1) {
                    
                    distance[r][c] = dist + 1;
                    min_heap.push({dist + 1, r, c});
                }
            }
        }

        return max_dist;
    }

    int maxDistance(vector<vector<int>>& grid) {
        // return djikstraSol(grid);
        return bfsSol(grid);
    }
};
