/*
    https://leetcode.com/problems/number-of-operations-to-make-network-connected/
    
    Idea is to find the number of disconnected components. Then we need to find the min edges
    required to keep the connected components connected, since this is not weighted so selecting any edge 
    is find as long as they are used for connecting atleast one unvisited node.
    
    Solution 1: Using BFS
    Solution 2 : Using Union-Find operation
*/
class Solution {
public:
    // Solution 1 : Using BFS
    // TC: O(V + E)
    int bfsSol(int& n, vector<vector<int>>& edges) {
        // create a graph from edges
        vector<vector<int>> g(n);
        for(auto edge: edges) {
            int u = edge[0], v = edge[1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        } 
        
        unordered_set<int> visited;
        int components = 0, edges_req = 0, total_edges = edges.size();
        // Now we do BFS to find the number of connected components as 
        // well as the number of enough edges required to make the connected
        // components still connected 
        for(int i = 0; i < n; i++) {
            // if the current node is unvisited, then it is a separate component
            if(!visited.count(i)) {
                queue<int> q;
                q.emplace(i);
                ++components;
                // mark it visited
                visited.emplace(i);
                
                while(!q.empty()) {
                    int curr = q.front();
                    q.pop();
                    // traverse only the unvisited adj nodes
                    for(auto neighbor: g[curr]) {
                        if(!visited.count(neighbor)) {
                            visited.emplace(neighbor);
                            q.emplace(neighbor);
                            ++edges_req;
                        }
                    }
                }
            }
        }
        
        int remaining_edges = total_edges - edges_req;
        return remaining_edges >= components - 1 ? components - 1 : -1;
    }
    
    // Finds the root of a node using path compression
    int getRoot(int &u, vector<int>& root) {
        while(u != root[u]) 
            u  = root[root[u]];
        return u;
    }
    
    // Find operation for two nodes
    bool findOp(int &u, int &v, vector<int>& root) {
        return getRoot(u, root) == getRoot(v, root);
    }
    
    // Weighted union
    void unionOp(int &u, int &v, vector<int>& root, vector<int>& size) {
        int root_u = getRoot(u, root);
        int root_v = getRoot(v, root);
        
        // to make the tree balanced across with, assign the
        // smaller component to the bigger one
        if(size[root_u] < size[root_v]) {
            root[root_u] = root_v;
            size[root_v] += size[root_u];
        }
        else {
            root[root_v] = root_u;
            size[root_u] += size[root_v];
        }
    }
    
    // Solution 2 : Using Union Find
    // TC: O(ElogV)
    int unionFindSol(int& n, vector<vector<int>>& edges) {
        int mst_edges = 0, total_edges = edges.size();
        vector<int> root(n), size(n, 1);
        // initialize root array for union-find
        for(int i = 0; i < n; i++)
            root[i] = i;
    
        for(auto edge: edges) {
            // add the edge only if one of
            // the vertices is unvisited
            if(!findOp(edge[0], edge[1], root)) {
                ++mst_edges;
                // mark them visited incase they are not visited yet
                // Union the nodes
                unionOp(edge[0], edge[1], root, size);
            }
        }
        
        int components = 0;
        for(int i = 0; i < n; i++)
            components = components + (root[i] == i);
        // check if the remaining edges are enough for the disconnected nodes 
        return (total_edges - mst_edges) >= components - 1?
                components - 1: -1;
    }
    
    int makeConnected(int n, vector<vector<int>>& connections) {
        // return bfsSol(n, connections);
        return unionFindSol(n, connections);
    }
};
