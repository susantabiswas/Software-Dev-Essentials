/*
    https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/submissions/
    
    TC: O(N)
    SC: O(N)
*/

class Solution {
    struct Edge {
        int endpt = -1;
        // whether the edge allows travel to endpt
        bool travel_allowed = true;
        
        Edge(int endpt, bool travel_allowed): 
            endpt(endpt), travel_allowed(travel_allowed) {};
    };
public:
    void dfs(int curr, vector<vector<Edge>>& g,
            unordered_set<int>& visited, int &changes) {
        
        // mark as visited
        visited.emplace(curr);
        
        // DFS with all the neighboring paths
        for(int i = 0; i < g[curr].size(); i++) {
            // if the neighbor is unvisited
            if(visited.count(g[curr][i].endpt) == 0) {
                // if the edge allows travel from current direction only,
                // it needs to be reoriented, since the neighbor won't be able to each 
                // the current node
                if(g[curr][i].travel_allowed)
                    ++changes;
                dfs(g[curr][i].endpt, g, visited, changes);
            }
        }
    }
    
    int minReorder(int n, vector<vector<int>>& connections) {
        // We create a graph, and for two connected nodes
        // add the path for both the nodes. Mark the edge
        // which directly allows travel as 'travel_allowed': true
        // false for the other.
        // Since each node is only connected via one path with the 
        // other node and we can only orient the direction of path,
        // means, we just have to find the edges that can't be used to 
        // travel from root to reach the rest of the nodes
        vector<vector<Edge>> g(n);
        for(auto edge: connections) {
            g[edge[0]].emplace_back(Edge(edge[1], true));
            g[edge[1]].emplace_back(Edge(edge[0], false));
        }
        
        // Do simple DFS to find the edges that doesnt let travel
        unordered_set<int> visited;
        // edge orientations required
        int changes = 0;
        dfs(0, g, visited, changes);
        return changes;
    }
};
