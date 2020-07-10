/*
    https://leetcode.com/problems/01-matrix/submissions/
    
    We do BFS for finding the shortest distance. We make the initial zeros
    as the sources for the BFS, then start BFS from those. For a node with 0 distance is 0.
    TC: O(MN)
*/
class Solution {
public:
    bool isValid(int& r, int& c, const int &row, const int &col) {
        return r >= 0 && r < row && c >= 0 && c < col;    
    }
    
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        if(matrix.empty())
            return matrix;
        
        queue<pair<int, int>> q;
        const int M = matrix.size(), N = matrix[0].size();
        int level = 0, level_nodes = 1;
        vector<vector<bool>> visited(M, vector<bool>(N, false));
        vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,-1}, {0,1}};
        
        // add all the 0 nodes as the source nodes
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++) {
                if(matrix[i][j] == 0) {
                    q.emplace(make_pair(i, j));
                    visited[i][j] = true;
                }
            }
        
        level_nodes = q.size();
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            --level_nodes;
            // update distance of nodes with 1
            if(matrix[curr.first][curr.second] == 1) {
                matrix[curr.first][curr.second] = level;
            }
            // add its adjacent non visited neighbors
            for(auto dir: dirs) {
                int r = dir[0] + curr.first;
                int c = dir[1] + curr.second;
                if(isValid(r, c, M, N) && !visited[r][c]) {
                    q.emplace(make_pair(r, c));
                    visited[r][c] = true;
                }
            }
            // End of a level
            if(level_nodes == 0) {
                ++level;
                level_nodes = q.size();
            }
        }
        
        return matrix;
    }
};
