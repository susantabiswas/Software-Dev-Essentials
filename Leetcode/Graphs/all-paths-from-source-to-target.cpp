/*
  https://leetcode.com/problems/all-paths-from-source-to-target/

  We can all the paths using DFS traversal from source to destination. Since
  the graph is acylic we don't have to worry about making sure the traversal 
  doesnt end in an infinite loop also.
  TC: O(v * 2^(v-2)), v = no. of vertices
  SC: O(v)

  The start and end points are fixed, so if there are V nodes, we are left with V-2 nodes
  to choose from for the intermediate path.
  Also for each of these intermediate nodes, there are 2 choices: include or exclude
  So we have 2 ^ (V-2) ways of creating paths

  Reference:
  https://leetcode.com/problems/all-paths-from-source-to-target/discuss/986429/Python-Iterative-DFS-with-detailed-time-complexity-and-visuals

  NOTE:
  For an undirected graph, we have O(V!) possible paths, since we can choose the permutation of each path as well as direction doesnt matter.
  But this since this is a DAG, A->B ~= B->A, only one of these can exist in the DAG, so we dont do permuation of nodes

  Hence nCk(Combinations -> ~ 2^N) and not nPk(Permutations ~ N!)

  Why did we use combinations nCk and not Permutations nPk?

    We should count a group of nodes (only once) and not count every permutation of the same group/combination.
    In other words, I should not count : Start -> A -> B -> End and Start -> B -> A -> End as two different paths, because in reality, the actual DAG is one of these two solutions (not both).

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
