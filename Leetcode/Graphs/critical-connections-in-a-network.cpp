/*
    https://leetcode.com/problems/critical-connections-in-a-network/submissions/

    Nice Explanation:
    https://www.hackerearth.com/practice/algorithms/graphs/articulation-points-and-bridges/tutorial/
    
    https://cp-algorithms.com/graph/bridge-searching.html
    
    
    Idea is that an edge will be bridge if on its removal the remainder gets disconnected, but if the
    remainder portion has a back edge to a vertex that comes before the edge we are considering , then
    it wont be disconnected even if that edge is removed.
    
    a--b---c
    |------|
    
    We we reove a-b edge also, they will be connected because c has a back edge to a. 
    NOTE: the backedge should be <= b to be considered not a bridge edge.
    
    
    TC: O(V + E)
*/

class Solution {
public:
    void findBridges(int curr, int& timer, vector<vector<int>>& g,
                    vector<bool>& visited, vector<int>& earliest_back_edge,
                    vector<int>& discovery_time,
                    vector<vector<int>>& bridges,
                    int parent = -1) {
        
        // mark as visited
        visited[curr] = true;
        discovery_time[curr] = earliest_back_edge[curr] = timer++;
        
        // for all its neighbors check if they have a back edge
        for(int v: g[curr]) {
            if(!visited[v]) {
                findBridges(v, timer, g,
                        visited, earliest_back_edge,
                        discovery_time, bridges, curr);
                
                // check if the subtree has a back edge with discovery time lesser than current vertex
                earliest_back_edge[curr] = min(earliest_back_edge[curr], earliest_back_edge[v]);
                // if the subtree doesnt have a back edge before or with current node,
                // then the current edge is a bridge
                if(earliest_back_edge[v] > discovery_time[curr])
                    bridges.emplace_back(vector<int>{curr, v});
            }
            // node was visited before and not parent, means it comes before current node
            else if(visited[v] && parent != v)
                earliest_back_edge[curr] = min(earliest_back_edge[curr], discovery_time[v]);
        }
    }
    
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // Create a graph
        vector<vector<int>> g(n);
        for(const auto& edge: connections) {
            g[edge[0]].emplace_back(edge[1]);
            g[edge[1]].emplace_back(edge[0]);
        }
        
        // Find all the bridges
        int timer = 1;
        vector<bool> visited(n, false);
        vector<int> earliest_back_edge(n, INT_MAX), discovery_time(n, -1);
        vector<vector<int>> bridges;
        
        for(int i = 0; i < n; i++)
            if(!visited[i])
                findBridges(i, timer, g, visited,
                           earliest_back_edge, 
                            discovery_time, bridges);
        return bridges;
    }
};
