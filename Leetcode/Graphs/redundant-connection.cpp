/*
    https://leetcode.com/problems/redundant-connection/
*/
/*
    https://leetcode.com/problems/redundant-connection/
*/
class Solution {
    class UnionFind {
        private:
            vector<int> root;
            vector<int> size;

        public:
            UnionFind(int n) {
                root.resize(n+1);
                for(int i = 0; i <= n; i++)
                    root[i] = i;
                
                size.resize(n+1, 1);
            }    
        
            int getRoot(int u) {
                while(u != root[u]) {
                    root[u] = root[root[u]];
                    u = root[u];
                }
                return u;
            }
        
            bool Union(int a, int b) {
                int root_a = getRoot(a);
                int root_b = getRoot(b);
                
                if(root_a == root_b)
                    return false;
                
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
        
            bool Find(int a, int b) {
                return getRoot(a) == getRoot(b);
            }
        
    };
public:
    
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        // find the max vertices
        int n = edges.size();
        UnionFind uf(n);
        
        vector<int> extra_edge;
        
        for(auto edge: edges) {
            if(!uf.Union(edge[0], edge[1])) {
                extra_edge = edge;
                break;
            }
        }
            
        return extra_edge;
    }
};
