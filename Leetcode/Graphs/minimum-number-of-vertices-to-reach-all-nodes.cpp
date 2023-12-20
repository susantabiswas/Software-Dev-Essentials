/*
    https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/
    
    A node which can reach all other nodes means it doesn't have any incoming edges,
    this is because the graph is acyclic and directed, if there is an edge coming to
    such a node, then that would create a cycle.
    
    With this, we know all such nodes will have no incoming edges. This is the basic idea to solve it.
    
    SOLUTION 1: 
    TC: O(V + E)
    SC: O(V + E)
    
    We create a reverse graph and use kahn's algo to traverse the graph using the indegree.
    In the reversed graph, all the sources will have no outgoing edges and we check for this condition.
    
    SOLUTION 2: Optimization
    TC: O(E)
    SC: O(V)
    
    We don't really need to create a reverse graph, instead just check for nodes with no incoming edges as
    explained above.
*/
class Solution {
public:
    vector<int> sol1(int n, vector<vector<int>>& edges) {
        vector<int> result;
        
        // create a reverse graph
        vector<vector<int>> g(n);
        for(auto edge: edges) {
            g[edge[1]].push_back(edge[0]);    
        }
        
        // Find all the nodes with no neighbors, these are the
        // node which can reach all other nodes in the orig graph
        for(int i = 0; i < n; i++)
            if(g[i].empty())
                result.push_back(i);
        
        return result;    
    }
    
    vector<int> sol2(int n, vector<vector<int>>& edges) {
        vector<bool> incoming_edge(n, false);
        
        for(auto edge: edges)
            incoming_edge[edge[1]] = true;
        
        vector<int> result;
        for(int node = 0; node < n; node++)
            if(!incoming_edge[node])
                result.push_back(node);
        
        return result;
    }
    
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        // return sol1(n, edges);
        return sol2(n, edges);
    }
};
