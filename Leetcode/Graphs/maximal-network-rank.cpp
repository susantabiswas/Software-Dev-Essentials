/*
    https://leetcode.com/problems/maximal-network-rank/
    
    TC: O(E + V^2)
    SC: O(V + E)
    
    Idea is to simply find out the indegree/degree for each node.
    Then for all the node pairs, we can count the rank easily with the indegree
    information.
    Note: If nodes are connected, make sure to decrease the total count by 1 (to account for duplicate count of common edge)
*/
class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        // node: [neighbors]
        unordered_map<int, unordered_set<int>> g;
        
        // indegree[i] = edges connected to ith node
        vector<int> indegree(n, 0);
        for(auto edge: roads) {
            ++indegree[edge[0]], ++indegree[edge[1]];
            
            g[edge[0]].insert(edge[1]);
            g[edge[1]].insert(edge[0]);
        }
        
        int max_rank = 0;
        
        // Since network rank is max of rank of all the node pairs
        // we find the network rank for each of the node pairs
        for(int i = 0; i < n; i++)
            for(int j = i + 1; j < n; j++) {
                // if the two nodes are connected, decrease the indegree count as
                // they both would have contributed to that count individually and made it 2
                int rank = indegree[i] + indegree[j] + (g[i].count(j) ? -1 : 0);
                
                // Optimization: We can skip the indegree array
                // Above line can also be calculated like below:
                // int rank = g[i].size() + g[j].size() + (g[i].count(j) ? -1 : 0);
                max_rank = max(max_rank, rank);
            }
                
        return max_rank;
    }
};
