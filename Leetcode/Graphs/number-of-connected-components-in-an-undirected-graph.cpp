/*
    https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
    
    Idea is to perform DFS from each unvisited node. If a node is unvisited that means that
    it is not part of any of the components visited so far.
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    void dfs(int node, vector<vector<int>>& graph,
            unordered_set<int>& visited) {
        // mark as visited
        visited.emplace(node);
        // explore unviisted neighbors
        for(auto dst: graph[node])
            if(!visited.count(dst)) 
                dfs(dst, graph, visited);
    }
    
    int countComponents(int n, vector<vector<int>>& edges) {
        // <node: [neighboring nodes]>
        vector<vector<int>> graph(n);
        // Create undirected graph
        for(auto edge: edges) {
            int src = edge[0], dst = edge[1];
            graph[src].emplace_back(dst);
            graph[dst].emplace_back(src);
        }
        
        int comps = 0;
        // Tracks visited nodes
        unordered_set<int> visited;
        
        // Perform DFS for each unvisited node source
        for(int node = 0; node < n; node++)
            // Node is unvisited, so it must be in a different unvisited component
            if(!visited.count(node)) {
                ++comps;
                dfs(node, graph, visited);
            }
        return comps;
    }
};
