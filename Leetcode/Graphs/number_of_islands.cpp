/*
    200. Number of Islands
    https://leetcode.com/problems/number-of-islands/
*/

class Solution {
public:
    // weighted union operation
    int weightedUnion(vector<int>& roots, vector<int>& num_nodes, int i, int j) {
        // find roots for both
        int root_i = find(roots, i);
        int root_j = find(roots, j);
        
        // if they have the same root
        if(root_i == root_j)
            return root_i;
        
        if(root_i != root_j) {
            if(num_nodes[root_i] > num_nodes[root_j]) {
                roots[root_j] = root_i;
                num_nodes[root_i] += num_nodes[root_j];
                return root_i;
            }
            else if(num_nodes[root_i] < num_nodes[root_j]) {
                roots[root_i] = root_j;
                num_nodes[root_j] += num_nodes[root_i];
                return root_j;
            }
            else {  // i--> j
                roots[root_i] = root_j;
                num_nodes[root_j] += num_nodes[root_i];
                return root_j;
            }
        }
        return -1;
    }
    
    // find operation using path compression
    int find(vector<int>& roots, int idx) {
        while(roots[idx] != idx) {
            roots[idx] = roots[roots[idx]];  
            idx = roots[idx];
        }
        return idx;
    }
    
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty())
            return 0;
        
        // no. of vertices
        const int N = grid.size() * grid[0].size();
        // for storing the root element
        vector<int> roots(N);
        // for deciding the rank, store the number of elements under each root
        vector<int> num_nodes(N, 1);
        
        int conn_islands = 0;
        
        const int n = grid.size();
        const int m = grid.front().size();
        for(int i = 0; i < grid.size()-1; i++) {
            for(int j = 0; j < grid.front().size()-1; j++) {
                if(grid[i][j] == '1' && grid[i][j+1] == '1')
                    weightedUnion(roots, num_nodes, i*m + j, i*m + j + 1);
                
                if(grid[i][j] == '1' && grid[i+1][j] == '1')
                    weightedUnion(roots, num_nodes, i*m + j, (i+1)*m + j);
            } 
        }
        
        for(int i = 0; i < roots.size(); i++)
            if(roots[i] == i)
                ++conn_islands;
        return conn_islands;
    }
};
