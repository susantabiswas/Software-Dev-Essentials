/*  
    https://leetcode.com/problems/kill-process/
    
    Core idea is to build a graph with the data provided. Once that is
    done, it is just a simple traversal problem from the source node which is
    kill node.
*/
class Solution {
public:
    void dfs(int node, unordered_map<int, vector<int>>& graph,
            vector<int>& nodes) {
        // process the current node
        nodes.emplace_back(node);
        // Explore its child processes
        for(auto child: graph[node])
            dfs(child, graph, nodes);
    }
    
    // TC: O(n)
    // SC: O(n)
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        // <parent node, [child node]>
        unordered_map<int, vector<int>> graph;
        
        // Construct the graph. Parent (ppid) -> node (pid)
        for(int i = 0; i < ppid.size(); i++)
            graph[ppid[i]].emplace_back(pid[i]);
        
        vector<int> nodes;
        // Start traversal from the source node
        dfs(kill, graph, nodes);
        return nodes;
    }
};
