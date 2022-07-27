/*
    https://leetcode.com/problems/largest-color-value-in-a-directed-graph/
    
    Core idea is to first process the nodes that come first in terms of dependency order.
    This ensures that when we process a node, all the paths coming to that node have been processed and
    the node will be processed at the end.
    
    Since we want to explore each path, naive DFS for each path will give TLE.
    We need to save the path color information. To do so, we can use a vector of size 26 for each node.
    This keeps track of longest length path with a given color appearing most frequently.
    
    SOLUTION 1: TOPOLOGICAL SORT (Kahn's Algo)
    In Kahn's algo, each time we are reducing the indegree, we are basically concluding the path traversed
    till that node. So we can do an extra step here, we also give that node the info of max color paths ending there.
    Keep passing on the path color info to each level. Also we use a var to keep track of max value seen so far.
    
    SOLUTION 2: DFS + DP
    This is also topological sort but with DFS. Just like topological sort with DFS, we first explore the neighboring nodes.
    Now here we save the path color info for each node if the traversal starts from there.
    So when a neighbor is done processing, just check the color path lengths that are possible from that neighbor
    and update the info of current node accordingly. Again a var is used to keep track of max value seen.
*/
class Solution {
public:
    // SOLUTION 1: TOPOLOGICAL SORT
    // TC: O(V + E)
    // SC: O(V + E)
    int topologicalSol(vector<unordered_set<int> >& graph, string& colors) {
        int n = graph.size(), processed = 0;
        queue<int> q;
        // indegree[i] = No. of incoming edges to node i
        vector<int> indegree(n, 0);
        // color_path_len[i][c] = For each color c,
        // stores the max no. of times c has been seen in a path ending here at node i  
        vector<vector<int> > color_path_len(n, vector<int>(26, 0));
        // Overall longest same colored nodes in a path
        int max_color = -1;
        
        // Find the indegree for each node
        for(int node = 0; node < n; node++)
            for(auto neighbor: graph[node])
                ++indegree[neighbor];
        
        // Add all the 0 indegree nodes
        for(int node = 0; node < n; node++)
            if(indegree[node] == 0)
                q.emplace(node);
        
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            ++processed;
            
            // Update the max color path info for the current node
            max_color = max(max_color, ++color_path_len[node][colors[node] - 'a']);
                
            // Remove edge from each neighbor
            for(auto neighbor: graph[node]) {
                --indegree[neighbor];
                if(indegree[neighbor] == 0)
                    q.emplace(neighbor);
                
                // Update the color path info for the neighbor
                for(int color = 0; color < 26; color++) {
                    color_path_len[neighbor][color] = max(color_path_len[neighbor][color],
                                                         color_path_len[node][color]);
                }
            }
        }
        
        return processed < n ? -1 : max_color;
    }
    
    bool dfs(int node, vector<unordered_set<int> >& graph, string& colors, 
             vector<int>& visited, vector<vector<int> >& color_path_len, int& max_color) {
        // Node is currently under processing and we are again seeing it, means a cycle
        if(visited[node] == 1)
            return false;
        
        // Node is unvisited
        if(visited[node] == 0) {
            // Mark node as processing
            visited[node] = 1;
            
            // Explore the neighbors first
            for(auto neighbor: graph[node]) {
                if(!dfs(neighbor, graph, colors, visited, color_path_len, max_color))
                    return false;
                // Since all the paths starting this neighbors have been explored, get the
                // max color path info
                for(int color = 0; color < 26; color++) {
                    color_path_len[node][color] = max(color_path_len[node][color],
                                                     color_path_len[neighbor][color]);
                    max_color = max(max_color, color_path_len[node][color]);
                }
            }
            // Update the color info for current node
            max_color = max(max_color, ++color_path_len[node][colors[node] - 'a']);
            
            // Mark as visited
            visited[node] = 2;
        }
        return true;
    }
    
    // SOLUTION 2: DFS + DP
    // TC: O(V + E)
    // SC: O(V + E)
    int dfsDpSol(vector<unordered_set<int> >& graph, string& colors) {
        int max_color = -1, n = graph.size();
        // visited[i] = {0 (Unvisited), 1 (Processing), 2(Visited)}
        vector<int> visited(n, 0);
        // color_path_len[i][c] = For each color c,
        // stores the max no. of times c has been seen in a path start from here at node i  
        vector<vector<int> > color_path_len(n, vector<int>(26, 0));
        
        for(int node = 0; node < n; node++)
            if(!dfs(node, graph, colors, visited, color_path_len, max_color))
                return -1;
        return max_color;
    }
    
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        // <node, [neighbors] >
        vector<unordered_set<int> > graph(colors.size());
        
        // create the graph
        for(auto edge: edges) 
            graph[edge[0]].emplace(edge[1]);
        
        // return topologicalSol(graph, colors);
        return dfsDpSol(graph, colors);
    }
};
