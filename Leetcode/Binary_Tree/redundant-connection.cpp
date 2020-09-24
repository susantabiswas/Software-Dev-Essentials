/*
    https://leetcode.com/problems/redundant-connection/submissions/
    
    Idea is to use union-find to find the connected nodes.
    Initially the set of tree nodes = {}
    We start adding each edge to the the tree iff the two edges are not connected
    by a network of edges, incase they are connected keep track of this extra edge.
    Continue for all th edges and return the extra edge in the end.
    
    TC: O(ElogV)
*/

class Solution {
public:
    // Weighted Union
    // TC: O(logV)
    void unionOp(int &u, int &v, 
        vector<int> &root, vector<int> &size){
        
        // get the roots 
        int root_u = getParent(u, root);
        int root_v = getParent(v, root);
        
        // In order to keep it balanced, branch out the 
        // bigger root
        if(size[root_u] > size[root_v]) {
            size[root_u] += size[root_v];
            root[root_v] = root_u;
        }
        else {
            size[root_v] += size[root_u];
            root[root_u] = root_v;
        }
    }
    
    // Find using path compression
    // TC: O(logV)
    int getParent(int u, vector<int> &root) {
        while(u != root[u]) {
            u = root[root[u]];
        }
        return u;
    }
    
    bool findOp(int &u, int &v, 
        vector<int> &root, vector<int> &size) {
        return getParent(u, root) == getParent(v, root);
    }
    
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        // We can use Union - Find for this
        // since there are distinct 1..N nodes, we need N-1 edges
        // and we know we have one extra
        int vertices = edges.size();
        // init the union-find root vector
        vector<int> root(vertices + 1), size(vertices + 1, 1);
        for(int i = 0; i < vertices; i++)
            root[i] = i;
        
        vector<int> extra_edge;
        
        for(auto &edge: edges) {
            if(findOp(edge[0], edge[1], root, size)) 
                extra_edge = edge;
            else
                unionOp(edge[0], edge[1], root, size);
        }
        
        return extra_edge;    
    }
};
