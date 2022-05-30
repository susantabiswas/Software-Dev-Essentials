/*
    https://leetcode.com/problems/01-matrix/
    
    
    The problem can be thought of as shortest path problem.
    For any of the nodes with 1, the source can be any of the 0 nodes.
    We can use either BFS or Djikstra to find the shortest distance to each node
    from the source nodes.
    
    Solution 1: Djikstra
    TC: O(MNlog(MN))
    SC: O(MN)
    
    Solution 2: BFS
    TC: O(MN)
    SC: O(MN)
*/
class Solution {
public:
    vector<vector<int>> djikstraSol(vector<vector<int>>& mat) {
        int M = mat.size(), N = mat[0].size();
        vector<vector<int>> distance(M, vector<int>(N, -1));
        
        auto comp = [&](const array<int, 3>& a, const array<int, 3>& b) { return a[0] > b[0]; };
        priority_queue<array<int, 3>, vector<array<int, 3> >, decltype(comp)> min_heap(comp);
        
        // Add the source nodes with 0
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                if(mat[i][j] == 0)
                    min_heap.push({0, i, j});
        
        vector<vector<int>> directions = {{1, 0}, {-1, 0},
                                          {0, 1}, {0, -1}};
        
        while(!min_heap.empty()) {
            auto [dist, row, col] = min_heap.top();
            min_heap.pop();
            
            // already processed, so skip 
            if(distance[row][col] != -1)
                continue;
            
            // set the dist
            distance[row][col] = dist;
            
            // visit the unvisited neighbor
            for(auto direction: directions) {
                int r = row + direction[0], c = col + direction[1];
                
                // check for out of bound and then if that neighbor is  
                // unvisited node with 1
                if(r >= 0 && r < M && c >= 0 && c < N
                  && distance[r][c] == -1 && mat[r][c] == 1) {
                    min_heap.push({dist + 1, r, c});
                } 
            }
        }
        
        return distance;
    }
    
    // Sol 2: BFS Solution
    // TC: O(MN)
    // SC: O(MN)
    vector<vector<int>> bfsSol(vector<vector<int>>& mat) {
        int M = mat.size(), N = mat[0].size();
        vector<vector<int>> distance(M, vector<int>(N, -1));
        
        queue<array<int, 3>> q;
        
        // Add the source nodes with 0
        for(int i = 0; i < M; i++)
            for(int j = 0; j < N; j++)
                if(mat[i][j] == 0) {
                    q.push({0, i, j});
                    distance[i][j] = 0;
                }
        
        vector<vector<int>> directions = {{1, 0}, {-1, 0},
                                          {0, 1}, {0, -1}};
        
        while(!q.empty()) {
            auto [dist, row, col] = q.front();
            q.pop();
            
            // visit the unvisited neighbor
            for(auto direction: directions) {
                int r = row + direction[0], c = col + direction[1];
                
                // check for out of bound and then if that neighbor is  
                // unvisited node with 1
                if(r >= 0 && r < M && c >= 0 && c < N
                  && distance[r][c] == -1 && mat[r][c] == 1) {
                    q.push({dist + 1, r, c});
                    // set the dist
                    distance[r][c] = dist + 1;
                } 
            }
        }
        
        return distance;
    }
    
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        // return djikstraSol(mat);
        return bfsSol(mat);
    }
};


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
