/*
    431 · Connected Component in Undirected Graph
    https://www.lintcode.com/problem/431/

    TC: O(V + E)
    SC: O(V)

    Simple DFS while keeping track of elements visited.
*/
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */

class Solution {
public:
    void dfs(UndirectedGraphNode* curr, vector<UndirectedGraphNode*>& g,
            unordered_set<UndirectedGraphNode*>& visited, vector<int>& conn_nodes) {
        // mark as visited
        visited.emplace(curr);
        // process curr node
        conn_nodes.emplace_back(curr->label);
        // visit unvisited neighbors
        for(auto dst: curr->neighbors)
            if(visited.count(dst) == 0) {
                dfs(dst, g, visited, conn_nodes);
            }
    }

    /**
     * @param nodes: a array of Undirected graph node
     * @return: a connected set of a Undirected graph
     */
    vector<vector<int>> connectedSet(vector<UndirectedGraphNode*> nodes) {
        int n = nodes.size();
        unordered_set<UndirectedGraphNode*> visited;
        vector<vector<int>> result;

        // Do DFS to find the connected components
        for(auto v: nodes) {
            if(!visited.count(v)) {
                vector<int> conn_nodes;
                dfs(v, nodes, visited, conn_nodes);
                sort(conn_nodes.begin(), conn_nodes.end());
                result.emplace_back(conn_nodes);
            }
        }
        return result;
    }
};
