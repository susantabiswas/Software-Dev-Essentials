/*
    https://leetcode.com/problems/rotting-oranges/submissions/
    
    This matrix can be considered as a graph
    We do BFS, where the rotten oranges are taken as the valid 
    nodes to traverse, if after BFS there is any unreachable node
    then it is impossible to rot all oranges.
    
    TC: O(MN)
*/
class Solution {
public:
    int maxRotTime(vector<vector<int>>& grid) {
        queue<pair<int, int>> q;
        // keeps track of visited positions
        const int M = grid.size(), N = grid[0].size();
        
        // add the initial rotten oranges
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                if(grid[i][j] == 2) {
                    q.emplace(make_pair(i, j));
                    // Make the current pos visited by making it empty
                    grid[i][j] = 0;
                }
        
        int n_level = q.size(), level = 0;
        vector<vector<int>> dirs = {{1, 0}, {-1, 0},
                                    {0, 1}, {0, -1}};
        while(!q.empty()) {
            auto pos = q.front();
            q.pop();
            --n_level;
            // check its neighbors
            for(auto dir: dirs) {
                int r = pos.first + dir[0];
                int c = pos.second + dir[1];
                // the current neighbor can only help in propagating 
                // rotten oranges if it is rotten or it is fresh and gets rotten now
                if(r >= 0 && r < M && c >= 0 && c < N
                   && grid[r][c] != 0) {
                    q.emplace(make_pair(r, c));
                    // Make the current pos visited by making it empty
                    grid[r][c] = 0;
                }
            }
            // One level has ended, which is equal to 1min
            if(n_level == 0 && !q.empty()) {
                ++level;
                n_level = q.size();
            }
        }
        
        // check if all the oranges got rotten or not
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                if(grid[i][j] == 1)
                    return -1;
        return level;
    }

    
    int orangesRotting(vector<vector<int>>& grid) {
        return maxRotTime(grid);        
    }
};



