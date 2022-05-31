/*
    https://leetcode.com/problems/keys-and-rooms/
    
    This is a simple graph traversal problem. We can use dfs
    to do traversal from source node 0 and during dfs also return the
    number of nodes visited, at last check if we visited all the nodes.
    
    TC: O(V + E)
    SC: O(V)
*/
class Solution {
public:
    int dfs(int curr, vector<vector<int>>& graph, vector<bool>& visited) {
        // mark as visited
        visited[curr] = true;

        int n_subtree_nodes = 1;
        // visit the neighbors
        for(auto neighbor: graph[curr])
            if(!visited[neighbor]) {
                visited[neighbor] = true;
                n_subtree_nodes += dfs(neighbor, graph, visited);
            }
        return n_subtree_nodes;
    }

    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        vector<bool> visited(rooms.size(), false);
        // mark starting room as visited
        visited[0] = true;

        return dfs(0, rooms, visited) == rooms.size();        
    }
};
