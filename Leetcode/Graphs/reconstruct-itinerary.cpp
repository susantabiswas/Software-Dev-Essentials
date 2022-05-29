/*
    https://leetcode.com/problems/reconstruct-itinerary/
    
    This problem is about finding the Euler path. Euler path is a path
    which involves traversing all the edges only once.
    The way the algo works is, we start with a source and start traversing the outward
    edges it has, each time we remove that edge so that we don't process that edge even if come 
    back to this node again. We keep traversing till we hit a node, from where we can't move forward
    either due to all the outward edges being used already or lack of outward edges.
    When we hit a terminal node, we know that this is a node that should come after any remaining unvisited nodes.
    because we pick an edge without any core logic, we might traverse a path that skips other nodes,
    so when in this path we hit a roadblock we need to store that node in such a way that this comes after 
    the nodes that are yet to traversed. 
    So we save the node in a stack, return to the previous node. There check if there are any other edges are yet
    not traversed, if yes then traverse else add this node as well and return to the previous stack call.
    Since all the nodes are stored in a stack manner, path starts from the top element.
    
    TC: O(V + E) + O(ElogE) + O(E) // graph construction + sorting + Euler traversal
    SC: O(V + E)
    
    Ref:
    https://www.youtube.com/watch?v=8MpoO2zA2l4
*/
class Solution {
public:
    void eulerPath(string curr, 
               unordered_map<string, deque<string>>& g,
               vector<string>& order) {
        // traverse the neighboring edges
        while(!g[curr].empty()) {
            // use the current edge, since in a euler path
            // each edge is used only once, remove it
            auto edge = g[curr].front();
            g[curr].pop_front();
            eulerPath(edge, g, order);
        }
        // add the curr node, as there is no other way from here
        order.emplace_back(curr);
    }
    
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // create the graph, all the edges need to be sorted lexographically
        unordered_map<string, deque<string>> g;
        for(auto edge: tickets)
            g[edge[0]].emplace_back(edge[1]);
        
        // sort the edges lexographically
        for(auto [vertex, edges]: g)
            sort(g[vertex].begin(), g[vertex].end());
        
        vector<string> order;
        eulerPath("JFK", g, order);
        // During finding the Euler path, the nodes which should be visited
        // later can be found in front of order vector, so reverse it
        reverse(order.begin(), order.end());
        return order;
    }
};
