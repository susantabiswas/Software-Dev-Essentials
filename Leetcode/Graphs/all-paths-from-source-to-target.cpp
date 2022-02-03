/*
  https://leetcode.com/problems/all-paths-from-source-to-target/

  We can all the paths using DFS traversal from source to destination. Since
  the graph is acylic we don't have to worry about making sure the traversal 
  doesnt end in an infinite loop also.
  TC: O(V + E)
*/
class Solution {
public:
    void dfs(int curr, vector<vector<int>>& graph, 
             vector<int> curr_path, vector<vector<int>>& paths) {
        // add current node to path
        curr_path.emplace_back(curr);
        
        // if destination node is reached
        if(curr == graph.size() - 1) {
            paths.emplace_back(curr_path);
            return;
        }
        // DFS for all its neighbours
        for(auto neighbour: graph[curr]) {
            dfs(neighbour, graph, curr_path, paths);
        }
    }
    
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> paths;
        
        dfs(0, graph, vector<int>{}, paths);
        return paths;
    }
};
