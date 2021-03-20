/*
    https://leetcode.com/problems/number-of-provinces/submissions/
    
    1. We can use Union-Find algorithm to find the connected components.
    TC: O(ElogV) + O(V)
    SC: O(V)
    
    2. We can use DFS for finding connected nodes, each time we come across
        an unvisited node, we update connected_component += 1
        TC: O(N^2)
        SC: O(N)
*/

class Solution {
public:
    class UnionFind {
        private:
            vector<int> root_;
            vector<int> size_;
        public:
            UnionFind(int n) {
                root_.resize(n);
                size_.resize(n, 1);
                for(int i = 0; i < n; i++)
                    root_[i] = i;
            }
        
            int getRoot(int idx) {
                // Find using Path compression
                while(idx != root_[root_[idx]]) {
                    root_[idx] = root_[root_[idx]];
                    idx = root_[idx];
                }
                return idx;
            }
        
            bool Find(int u, int v) {
                return getRoot(u) == getRoot(v);
            }
        
            void Union(int u, int v) {
                // Union by Rank 
                int root_u = getRoot(u);
                int root_v = getRoot(v);
                
                if(size_[u] > size_[v]) {
                    root_[root_v] = root_u;
                    size_[root_u] += size_[root_v];
                }
                else {
                    root_[root_u] = root_v;
                    size_[root_v] += size_[root_u];
                }
            }
        
            int connectedComponents() {
                int conn_comps = 0;
                for(int i = 0; i < root_.size(); i++)
                    if(root_[i] == i)
                        ++conn_comps;
                return conn_comps;
            }
    };
    
    // TC: O(ElogV => N^2logN)
    // SC: O(N)
    int unionFindSol(vector<vector<int>>& isConnected) {
        UnionFind union_find = UnionFind(isConnected.size());
        
        for(int i = 0; i < isConnected.size(); i++)
            for(int j = 0; j < isConnected[0].size(); j++)
                // if the components are not connected already 
                // (since it is a undirected graph, the same edge connection might have happened)
                if(isConnected[i][j] && !union_find.Find(i, j))
                    union_find.Union(i, j);
        
        return union_find.connectedComponents();
    }
    
    // DFS driver for an adjacency matrix
    void dfs(vector<vector<int>> &graph, vector<bool> &visited,
            int curr) {
        if(visited[curr])
            return;
        // mark current as visited
        visited[curr] = true;
        // traverse its unvisited neighbors
        for(int neighbor = 0; neighbor < visited.size(); neighbor++)
            if(!visited[neighbor] && graph[curr][neighbor])
                dfs(graph, visited, neighbor);
    }
    
    // TC: O(N^2)
    // SC: O(N)
    int dfsSol(vector<vector<int>>& isConnected) {
        const int N = isConnected.size();
        vector<bool> visited(N, false);
        int conn_comps = 0;
        
        // Check for all unvisited nodes and do DFS to
        // visited connected nodes
        for(int src = 0; src < N; src++)
            for(int dst = 0; dst < N; dst++)
                // Start of a disconnected node
                if(!visited[src] && isConnected[src][dst]) {
                    ++conn_comps;
                    dfs(isConnected, visited, dst);
                }
                    
        return conn_comps;
    }
    
    int findCircleNum(vector<vector<int>>& isConnected) {
        // return unionFindSol(isConnected);
        return dfsSol(isConnected);
    }
};
