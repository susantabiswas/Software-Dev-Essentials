/*
    https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/
    
    TC: O(Elogn + E)
    
    Idea is to use UnionFind to find the min no. of edges needed to make the graph connected.
    Now at first we build the graph with the common edges.
    Next for both Alice and Bob we, do UnionFind on top of the graph built with the common edges.
    This will result in the addition of edges not covered by the common edges that can enable Bob and Alice
    to traverse the entire graph.
*/
class Solution {
private:
    class UnionFind {
    public:
        vector<int> root, size;
        // No. of edges processed
        int edges_processed = 0;
        // No. of nodes in the graph
        int n = 0;
        
        UnionFind(int n_) {
            n = n_;
            size.resize(n, 1), root.resize(n);
            for(int i = 0; i < n; i++)
                root[i] = i;
        }
        
        // Copy the state from input object
        void Copy(UnionFind* ob) {
            // Copy the root and size values
            for(int i = 0; i < n; i++)
                root[i] = ob->root[i];
            for(int i = 0; i < n; i++)
                size[i] = ob->size[i];
            // Copy the no. of edges processed
            edges_processed = ob->edges_processed;
        }
        
        int getRoot(int a) {
            while(a != root[a]) {
                root[a] = root[root[a]];
                a = root[a];
            }
            return a;
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
                ++edges_processed;
                return true;
            }
            return false;
        }
    };
    
public:
    UnionFind connectEdges(int edge_type, int n, int& edges_used,
                     vector<vector<int>>& edges, UnionFind* ob = nullptr) {
        UnionFind uf(n);
        // Copy the state of the Unionfind object if not null
        if(ob)
            uf.Copy(ob);
        
        for(int i = 0; i < edges.size() && uf.edges_processed < n-1; i++) {
            int type = edges[i][0], src = edges[i][1] - 1, dst = edges[i][2] - 1;
            // Only process the edge meant for the current type
            if(type == edge_type && uf.Union(src, dst))
                ++edges_used;
        }
        return uf;
    }
    
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        int edges_used = 0;
        
        // Add the common edges to the graph
        auto common_graph = connectEdges(3, n, edges_used, edges);
        // Only add the edges need by Alice and Bob to traverse the rest of the graph
        // We pass the unionFind state of common graph, so that edges needed by Bob and 
        // Alice don't include the common edges alreayd available
        auto A_accessible_graph = connectEdges(1, n, edges_used, edges, &common_graph);
        auto B_accessible_graph = connectEdges(2, n, edges_used, edges, &common_graph);
        
        return (A_accessible_graph.edges_processed == n-1 && B_accessible_graph.edges_processed == n-1) ?
            edges.size() - edges_used : -1;
    }
};
