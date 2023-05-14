/*
    https://leetcode.com/problems/max-area-of-island/
    
    SOLUTION 1: DFS
    Idea is simply keep track of no. of nodes during dfs and pick the max
    nodes out of all connected components.
    
    TC: O(MN)
    SC: O(MN), recursive stack
    
    SOLUTION 2: Union-Find
    
    Using union-find find the connected components, then finally find the
    max sized component.
    TC: O(ElogV) => O(2MN * log(MN)) ~ O(MNlogMN),
        for each cell, we check its left and right cells i.e 2 cells 
    SC: O(MN)
*/
class Solution {
public:
    ///////////////////////////////////////////// SOLUTION 2: Union-Find //////////////////////
    class UnionFind {
    public:
        vector<int> size, root;
        
        UnionFind(int n) {
            size.resize(n, 1);
            root.resize(n, 1);
            
            for(int i = 0; i < n; i++)
                root[i] = i;
        }
        
        int getRoot(int idx) {
            while(idx != root[idx]) {
                root[idx] = root[root[idx]];
                idx = root[idx];
            }
            return idx;
        }
        
        bool Union(int a, int b) {
            int root_a = getRoot(a);
            int root_b = getRoot(b);
            
            if(root_a != root_b) {
                if(size[root_a] > size[root_b]) {
                    size[root_a] += size[root_b];
                    root[root_b] = root_a;
                }
                else {
                    size[root_b] += size[root_a];
                    root[root_a] = root_b;
                }
                return true;
            }
            return false;
        }
    };
    
    // Whether a valid position and it is a 1 cell
    bool isValid(int r, int c, vector<vector<int>>& grid) {
        return r >= 0 && r < grid.size() &&
            c >= 0 && c < grid.front().size() &&
            grid[r][c];
    }
    
    int unionFindSol(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid.front().size();
        UnionFind uf(m * n);    
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                // check right if that is 1, then join
                if(grid[i][j] && isValid(i, j+1, grid))
                    uf.Union(i*n + j, i*n + j + 1);
                // check bottom if that is 1, then join
                if(grid[i][j] && isValid(i+1, j, grid))
                    uf.Union(i*n + j, (i+1)*n + j);
            }
        }
        
        int max_area = 0;
        for(int r = 0; r < m; r++)
            for(int c = 0; c < n; c++)
                if(grid[r][c])
                    max_area = max(max_area, uf.size[r*n + c]);
        return max_area;
    }
    
    ///////////////////// SOLUTION 1: DFS
    int dfs(int i, int j, vector<vector<int>>& grid) {
        // out of bound check
        if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()
          || grid[i][j] == 0)
            return 0;
        // mark as visited
        grid[i][j] = 0;
        // DFS in all 4 directions
        return 1 + dfs(i+1, j, grid) + dfs(i-1, j, grid) + dfs(i, j+1, grid) + dfs(i, j-1, grid);
    }
    
    // TC: O(MN)
    // SC: O(MN)
    int dfsSol(vector<vector<int>>& grid) {
        int max_area = 0;
        
        // Start dfs from all unvisited nodes, each dfs returns the size of
        // connected graph
        for(int i = 0; i < grid.size(); i++)
            for(int j = 0; j < grid[0].size(); j++)
                if(grid[i][j]) {
                    int area = dfs(i, j, grid);
                    max_area = max(max_area, area);
                }
                    
        return max_area;
    }
    
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        return dfsSol(grid);
        // return unionFindSol(grid);
    }
};
