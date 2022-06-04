/*
    https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/
    
    TC: O(n^2 * logn), n^2 for creating the graph and each Union Find op takes O(logn)
    SC: O(n)
    
    If you plot the coordinates on a graph, it is pretty clear that in order to remove most
    no. of stones, we need first find the stones which are on the same row or col on the graph.
    For two stones, if they share either a col or row, it will make an edge. This way we create 
    the graph with all the edges.
    Then for a connected component, we can remove all the nodes except for one and that will be
    the answer for that component.
*/
class Solution {
private:
    
    class Unionfind {
    public:
        vector<int> root, size;
        
        Unionfind(int n) {
            root.resize(n);
            for(int i = 0; i < n; i++)
                root[i] = i;
            
            size.resize(n, 1);
        }
        
        int getRoot(int a) {
            while(a != root[a]) {
                root[a] = root[root[a]];
                a = root[a];
            }
            return a;
        }
        
        bool find(int a, int b) {
            return getRoot(a) == getRoot(b);
        }
        
        void Union(int a, int b) {
            int root_a = getRoot(a);
            int root_b = getRoot(b);
            
            if(root_a != root_b) {
                if(size[root_a] > size[root_a]) {
                    size[root_a] += size[root_b];
                    root[root_b] = root_a;
                }
                else {
                    size[root_b] += size[root_a];
                    root[root_a] = root_b;
                }
            }
        }
    };
    
public:
    int removeStones(vector<vector<int>>& stones) {
        Unionfind uf(stones.size());
        
        // create the graph
        for(int src = 0; src < stones.size(); src++)
            for(int dst = src + 1; dst < stones.size(); dst++) 
                // If any of the points have a common row or col, they can form an edge
                if(stones[src][0] == stones[dst][0] || stones[src][1] == stones[dst][1]) {
                    uf.Union(src, dst);
                }
        
        int removable = 0;
        // For all the connected components, all except one node can be removed from them
        for(int i = 0; i < uf.root.size(); i++)
            // For the current component, leave 1 node and remove rest
            if(uf.root[i] == i)
                removable += uf.size[i] - 1;
        return removable;
    }
};
