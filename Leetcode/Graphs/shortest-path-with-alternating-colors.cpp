/*
    https://leetcode.com/problems/shortest-path-with-alternating-colors/
    
    TC: O(V + E)
    SC: O(V + E)
    
    Idea is similar to normal BFS but with the some modification.
    Here a node might have multiple edges from it with diff colors.
    So a node might be used twice to follow the edge with a diff color from that node to reach some other node.
    
    Instead of standard visited[node] to track which node is visited, we
    use visited[node][color] to track the nodes visited and with which color.

3
[[0,1],[1,2]]
[]

5
[[0,1],[1,2],[2,3],[3,4]]
[[1,2],[2,3],[3,1]]

In the below test case, multiple nodes are visited twice
5
[[2,0],[4,3],[4,4],[3,0],[1,4]]
[[2,1],[4,3],[3,1],[3,0],[1,1],[2,0],[0,3],[3,3],[2,3]]

*/
class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        // create the graph
        // <node, [{dst, color}]
        unordered_map<int, vector<array<int, 2>> > g;
        
        // colors = -1 (uncolored), 0 (red), 1 (blue)
        for(auto edge: redEdges)
            g[edge[0]].push_back({edge[1], 0});
        for(auto edge: blueEdges)
            g[edge[0]].push_back({edge[1], 1});
        
        // <node, color>: whether the destination node with edge 'color' has been visited
        vector<vector<bool>> visited(n, vector<bool>(2, false));
        vector<int> dist(n, INT_MAX);
        
        // <node, dist, color>
        queue<array<int, 3>> q;
        q.push({0, 0, -1});
        
        while(!q.empty()) {
            auto [curr, d, c] = q.front();
            q.pop();
            
            dist[curr] = min(dist[curr], d);
            
            for(auto [dst, color]: g[curr]) {
                // only use the edge if that colored edge has not been used
                // to reach target `dst` before
                if(!visited[dst][color] && color != c) {
                    q.push({dst, d + 1, color});
                    visited[dst][color] = true;
                }
            }
        }
        
        for(int i = 0; i < n; i++)
            if(dist[i] == INT_MAX)
                dist[i] = -1;
        
        return dist;
    }
};
