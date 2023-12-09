/*
    https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/
    
    TC: O(E)
    SC: O(E)
    
    Points to note:
    - There wont be any cycle, so each node pair is connected via that edge only. We just have
    to worry about orienting that edge
    - Since all the nodes should reach the node 0, node 0 can be thought of as a tree and all the
    other nodes form the tree with root node 0
    
    Idea is to start the traversal from node 0, then for all of its neighbors, whichever neighbor's edge is not facing  towards the
    current parent, reverse their orientation and start dfs from that node in a similar manner
    
*/
class Solution {
public:
    void dfs(int curr, int parent, int& flips, vector<vector<array<int, 2> > >& g) {
        for(auto [dst, towards]: g[curr]) {
            // since we have created an undirected graph, we should skip the
            // edge coming from the parent node
            if(dst == parent)
                continue;
            
            // if the edge faces away from current, then flip it so that
            // it is towards the root from where we started percolating downwards
            if(!towards)
                ++flips;
            dfs(dst, curr, flips, g);
        }
    }
    
    int minReorder(int n, vector<vector<int>>& connections) {
        // create the graph with direction info
        // src : [(dst, towards src or not[bool])]
        vector<vector<array<int, 2> > > g(n);
        
        // create an undirected graph
        for(auto edge: connections) {
            int src = edge[0], dst = edge[1];
            // for A -> B
            // A: {B, towards=False}
            // B: {A, towards=True}
            g[src].push_back({dst, 0});
            g[dst].push_back({src, 1});
        }
        
        // start dfs from 0 and find out the reachability
        int flips = 0;
        dfs(0, -1, flips, g);
        return flips;
    }
};
