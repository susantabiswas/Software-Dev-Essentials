/*
    https://leetcode.com/problems/number-of-islands/
    
    Solution 1: DFS
    TC: O(V^2)
    
    Solution 2: Union-Find
    TC: O(2*MN * log(MN)) ~ O(MN * log(MN)), 
    There are 2 Edges checked for each node and there are M*N nodes
    
    Iterate through the nodes and for each node, check if it is a land mass and
    connect its right and bottom land masses if they are also land masses.
*/

////////////////// SOLUTION 1: DFS ///////////////////
class Solution {
public:
    void DFS(vector<vector<char>>& grid, int i, int j) {
        // boundary checking
        if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return;
        // return if current position is of water or is already visited
        if(grid[i][j] == '2' || grid[i][j] == '0')
            return;
        
        // mark the current as visited
        grid[i][j] = '2';
        
        // do DFS in all 4 directions
        DFS(grid, i+1, j);
        DFS(grid, i, j-1);
        DFS(grid, i-1, j);
        DFS(grid, i, j+1);
    }
    
    int numIslands(vector<vector<char>>& grid) {
        // We can treat the matrix grid as a grid. Each Island is a
        // connected component. The task is to find no. of disconnectedd components
        // in the graph.
        
        int islands = 0;
        // We make each 1 as 2 in when it is visited
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                // do DFS in case has not been visited and there is land
                if(grid[i][j] == '1') {
                    DFS(grid, i, j);
                    ++islands;
                } 
            }
        }
        return islands;
    }
};

//////////////////////// SOLUTION 2 : Union-Find ////////////////

class Solution {
public:
    class UnionFind {
    public:
        vector<int> root;
        vector<int> size;
    
        UnionFind(int n) {
            root.resize(n);
            for(int i = 0; i < n; i++)
                root[i] = i;
            size.resize(n, 1);
        }
        
        int getRoot(int a) {
            while(root[a] != a) {
                root[a] = root[root[a]];
                a = root[a];
            }
            return a;
        }
        
        bool Find(int a, int b) {
            return getRoot(a) == getRoot(b);
        }
        
        bool Union(int a, int b) {
            int root_a = getRoot(a);
            int root_b = getRoot(b);
            
            if(root_a != root_b) {
                if(size[root_a] > size[root_b]) {
                    root[root_b] = root_a;
                    size[root_a] += size[root_b];
                }
                else {
                    root[root_a] = root_b;
                    size[root_b] += size[root_a];
                }
                return true;
            }
            return false;
        }
    };
    
    bool isValid(int i, int j, int m, int n) {
        return i >= 0 && i < m &&
            j >= 0 && j < n;
    }
    
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        // Each of the cells are treated as graph nodes
        UnionFind uf(m * n);
        int islands = 0;
        
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++) {
                // Check if the current cell is a landmass that can be connected to
                // any existing right or bottom land mass
               if(isValid(i, j + 1, m, n) && grid[i][j] == '1' && grid[i][j+1] == '1')
                   uf.Union(i*n + j, i*n + (j+1));
                
               if(isValid(i+1, j, m, n) && grid[i][j] == '1' && grid[i+1][j] == '1')
                   uf.Union(i*n + j, (i+1)*n + j);
            }
        
         // Check no. of connected components that are land
         for(int i = 0; i < m; i++) 
            for(int j = 0; j < n; j++) 
                if(grid[i][j] == '1' && uf.root[i*n + j] == i*n + j) 
                    ++islands;
                    
        return islands;
    }
};
