/*
    https://leetcode.com/problems/find-center-of-star-graph/
    
    Star node will have connections from each node, so we find the
    indegree for each node and the max indegree node is the star node.
    
    TC: O(E + V)
    SC: O(V)
*/

class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        // compute the indegree of nodes
        unordered_map<int, int> indegree;
        
        // calculate the indegree of each node
        for(auto &edge: edges) 
            indegree[edge[0]]++, indegree[edge[1]]++;
        
        int star_node = 0, max_indegree = 0;
        // star node will have the max indegree,
        // find the node with max indegree
        for(unordered_map<int, int>::iterator it = indegree.begin();
           it != indegree.end(); it++) {
           if(it->second > max_indegree) {
               max_indegree = it->second;
               star_node = it->first;
           }
        }
        
        return star_node;
    }
};
