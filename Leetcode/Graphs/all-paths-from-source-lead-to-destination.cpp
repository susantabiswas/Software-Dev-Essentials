/*
    https://leetcode.com/problems/all-paths-from-source-lead-to-destination/
    
    TC: O(V + E)
    SC: O(V)
    
    Things to note:
    1. There should be no cycle, as we need to arrive at a terminal node and a cyclic path wont allow
        that.
    2. Target has no outgoing edges, means it is a leaf node. So when we reach a leaf node, check if it 
        is the target node
    3. We use the classic color finding algo to detect cycle in directed cyclic graph, but with an important change.
        In the classic version we return true in the end to signify that the current path did not see any
        cycle, but here if we should only return true if we were able to find the target with the current path.
        So to give a chance for that to happen, whenever we reach a leaf node, we check if it is the target node,
        if not return false, which makes the entire path false propagated upwards.
*/
class Solution {
public:
    bool dfs(int curr, int target, unordered_map<int, vector<int>>& g,
            vector<int>& color) {
        // if it is a terminal/leaf node, then condition is satisfied only
        // if it is the target node
        if(g[curr].empty())
            return curr == target;
        
        // processing curr node
        color[curr] = 0;
        
        for(auto neighbor: g[curr]) {
            // node is currently processing and
            // we have again encountered it, so a cycle is present
            if(color[neighbor] == 0)
                return false;
            // recurse the path if the neighbor is unprocessed
            if(color[neighbor] == -1 && !dfs(neighbor, target, g, color))
                return false;
        }
        // node processed
        color[curr] = 1;
        
        return true;
    }
    
    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
        // create the graph
        unordered_map<int, vector<int> > g;
        
        for(auto edge: edges)
            g[edge[0]].push_back(edge[1]);
        
        // -1 is unprocessed, 0: processing, 1: processed
        vector<int> color(n, -1);
        
        return dfs(source, destination, g, color);
    }
};
