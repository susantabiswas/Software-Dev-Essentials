/*
    https://leetcode.com/problems/connecting-cities-with-minimum-cost/
    
    Since we need to have all the nodes connected with min cost,
    this is a MST problem, we can Kruskal's MST algo to find the minimum cost of having the MST.
*/
class Solution {
private:
    class UnionFind {
    public:
        vector<int> root, size;
        UnionFind(int n) {
            root.resize(n);
            size.resize(n, 1);
            
            for(int i = 0; i < n; i++)
                root[i] = i;
        }
        
        int getRoot(int a) {
            while(root[a] != a) {
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
public:
    // TC: O(ElogE (sorting) + ElogV (Union))
    // SC: O(E (sorting) + V (UnionFind))
    int kruskalMST(int n, vector<vector<int>>& edges) {
        // sort the edges
        auto comp = [&](const vector<int>& a, const vector<int>& b) { return a[2] < b[2]; };
        sort(edges.begin(), edges.end(), comp);
        
        UnionFind uf(n);
        int cost = 0;
        
        int n_edges = 0;
        for(int i = 0; i < edges.size(); i++) {
            int src = edges[i][0] - 1, dst = edges[i][1] - 1, weight = edges[i][2];
            // edge can be added to MST, update the cost
            if(uf.Union(src, dst))
                cost += weight;
            // N-1 edges completed, exit
            if(n_edges == n-1)
                break;
        }
        // if it is possible to have all the cities connected, then there will be only one cluster
        // with size = n
        return uf.size[uf.getRoot(0)] == n ? cost : -1;
        
    }
    
    int minimumCost(int n, vector<vector<int>>& connections) {
        return kruskalMST(n, connections);
    }
};
