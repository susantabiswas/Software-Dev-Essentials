/*
    https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/
    
	NOTE: I tried Prims solution to find the different mst using different start vertex, but that doesnt work. I thought of creating the different
	MST using different start vertex and then keep frequency of the edges across all the mst. This would have worked if the algo gave different 
	MST topology, but it didnt. The standard MST implementation can still give the same MST topology and hence it doesnt work.
	
	Kruskal Solution
    TC: O(E + E * (ElogV)) (Edge iteration + for each edge * unionFind)
    SC: O(V + E), UnionFind + E new index entries made to each edge
    
    Points:
    1. MST cost is the min cost to connect all the nodes, there is only one such cost.
    2. There can be multiple MST that yield the same MST cost.
    3. Critical edge in MST is one, which when removed either increases the mst cost or makes the
        graph disconnected (might then give lower mst cost, since it will only be able to traverse some part of graph)
    4. Pseudo critical edge exist in atleast one MST, so even if it is removed, we should be able to get another MST that yield the
        same cost.
        
    With all the above info, we can do the following to check for critical and pseudo critical edges
    1. First compute the true mst cost
    2. Now we iterate through the edges:
        1. Find mst again without  this edges, if the new mst cost != orig cost, means this is a critical edge
        2. If cost is same, then this might be pseudo critical, so just skip this edge and again compute the mst,
            if we can get the same mst cost as orig, that means this edge is pseudo critical edge and we got the same
            cost via a different mst topology
*/
class Solution {
public:
    class UnionFind {
    public:
        vector<int> root, size;
        
        UnionFind(int n) {
            root.resize(n), size.resize(n, 1);
            for(int i = 0; i < n; i++)
                root[i] = i;
        }
        
        int getRoot(int i) {
            while(i != root[i]) {
                root[i] = root[root[i]];
                i = root[i];
            }
            
            return i;
        }
        
        bool Union(int a, int b) {
            int rootA = getRoot(a);
            int rootB = getRoot(b);
            
            if(rootA != rootB) {
                if(size[rootA] > size[rootB]) {
                    size[rootA] += size[rootB];
                    root[rootB] = rootA;
                }
                else {
                    size[rootB] += size[rootA];
                    root[rootA] = rootB;
                }
                return true;
            }
            return false;
        }
    };
    
    // Creates a MST with given conditions
    // skip_edge: index of edge to not include
    // init_edge: index of edge to include compulsorily
    int mstCost(int n, vector<vector<int>>& edges, int skip_edge=-1, int init_edge=-1) {
        UnionFind uf(n);
        
        int cost = 0;
        
        // include the initial edge if needed
        if(init_edge != -1) {
            uf.Union(edges[init_edge][0], edges[init_edge][1]);
            cost += edges[init_edge][2];
        }
        
        for(int i = 0; i < edges.size() && n > 1; i++) {
            if(i != skip_edge && uf.Union(edges[i][0], edges[i][1])) {
                cost += edges[i][2];
                --n;
            }
        }
        
        return cost;
    }
    
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        // since we need to return the edge index in final result, add the index info to each edge
        // <u, v, wt, edge index>
        for(int i = 0; i < edges.size(); i++)
            edges[i].push_back(i);
        
        // sort for union find
        sort(edges.begin(), edges.end(), [](vector<int>& a, vector<int>& b) {
           return a[2] < b[2]; 
        });
        
        // find the mst cost
        int mst_cost = mstCost(n, edges);
        
        vector<int> critical, pseudo;
        
        for(int i = 0; i < edges.size(); i++) {
            // an edge is critical if the mst cost increases or the graph becomes disconnected
            // for a disconnected graph, the mst cost will be diff from the orig true mst cost
            
            // skip the current edge and find the mst cost
            int new_cost = mstCost(n, edges, i);
            
            if(new_cost != mst_cost) {
                critical.push_back(edges[i][3]);
            }
            else {
                // this will be pseudo critical if fixing this edge, still results
                // in the same mst cost. That simply means that the current edge is part of 
                // atleast one or more MST
                
                new_cost = mstCost(n, edges, -1, i);
                if(new_cost == mst_cost)
                    pseudo.push_back(edges[i][3]);
            }
        }
        
        return { critical, pseudo };
    }
};
