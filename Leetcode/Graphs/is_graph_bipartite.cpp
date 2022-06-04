/*
    https://leetcode.com/problems/is-graph-bipartite/
    
    Core idea is to check whether we can color the graph nodes with just 2 colors
    such that the adjacent vertices don't get the same color. If we can do that, then 
    graph is bipartite.
    
    We can color the graph either using BFS or DFS.
*/
class Solution {
public:
    bool dfsColoring(int curr, vector<int>& color, 
                     vector<vector<int>>& graph) {
        
        for(auto neighbor: graph[curr]) {
            // unvisited neighbor, assign the other color
            if(color[neighbor] == -1) {
                color[neighbor] = !color[curr];
                if(!dfsColoring(neighbor, color, graph))
                    return false;
            }
            // visited node, if it has the same color, can't be bipartite
            else if(color[neighbor] == color[curr])
                return false;
        }   
        return true;
    }
    
    // Solution DFS
    // TC: O(N)
    // SC: O(N)
    bool dfsSol(vector<vector<int>>& graph) {
        // Two color values: 0 and 1
        vector<int> color(graph.size(), -1);
        
        // Source vertex colored with 1
        for(int node = 0; node < graph.size(); node++) {
            if(color[node] == -1) {
                color[node] = 1;
                if(!dfsColoring(node, color, graph))
                    return false;
            }
        }
        return true;
    }
    
    
    // Solution BFS
    // TC: O(N)
    // SC: O(N)
    bool bfsSol(vector<vector<int>>& graph) {
        vector<int> color(graph.size(), -1);
        
        for(int node = 0; node < graph.size(); node++) {
            if(color[node] == -1) {
                queue<int> q;
                q.push(node);
                // give it color 1
                color[node] = 1;
                
                while(!q.empty()) {
                    auto curr = q.front();
                    q.pop();
                    
                    for(auto neighbor: graph[curr]) {
                        if(color[neighbor] == -1) {
                            color[neighbor] = !color[curr];
                            q.push(neighbor);
                        }
                        else if(color[neighbor] == color[curr])
                            return false;
                    }
                }
            }
        }
        return true;
    }
    
    bool isBipartite(vector<vector<int>>& graph) {
        return dfsSol(graph);
        // return bfsSol(graph);
    }
};
