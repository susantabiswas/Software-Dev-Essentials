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

/*
    https://leetcode.com/problems/critical-connections-in-a-network/
    
    AP: Vertex which when removed will result in disconnection of graph at that point. If it's 
    root, then it should have atleast 2 children.
    Bridge: The Edge connecting the AP is called bridge. If it is removed, graph is disconnected.

    The core logic works on the principle of back edge. If a node B whose parent is A, has an edge to one of the
    ancestors of A, then even if A is removed B will not be disconnected with the rest of the graph.

    Sof we do a modified DFS where we record the discovery time of each node and also the earliest back edge
    it can connect to. When the DFS returns to the node, we check if the subtree has any backedge or not with
    any of the prior nodes. If it doesnt have one, then that is a bridge and the curr node is an Articulation Point.
    Another case is when the neighbor of curr node has been visited, if the neighbor is not the parent of curr node then
    that is a valid back edge. Update the back edge of curr node.
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    void findBridges(int curr, int& timer, vector<vector<int>>& graph,
                    vector<bool>& visited, vector<int>& discovery_time, vector<int>& earliest_back_edge,
                    vector<vector<int>>& bridges, int parent = -1) {
        
        // mark the current node as visited
        visited[curr] = true;
        // Set the discovery time and init the earliest known back edge value
        discovery_time[curr] = timer;
        earliest_back_edge[curr] = timer;
        ++timer;

        // Visit the neighboring nodes and determine whether a bridge is present
        // or not
        for(auto neighbor: graph[curr]) {
            // if neighbour is unvisited, dfs for it and later determine whether 
            // the edge is a bridge or not based on the earliest known backedge of 
            // neighbor
            if(!visited[neighbor]) {
                findBridges(neighbor, timer, graph, visited, discovery_time,
                            earliest_back_edge, bridges, curr);
                // Check if the curr node can reach a node with earlier discovery time via
                // the subtree with neighbor as root. 
                earliest_back_edge[curr] = min(earliest_back_edge[curr], earliest_back_edge[neighbor]);
                // If the subtree at neighbor can't find an earlier backedge, then it means
                // this edge is a bridge and the current node is an ARTICULATION POINT
                if(earliest_back_edge[neighbor] > discovery_time[curr]) 
                    bridges.push_back({curr, neighbor});
            }
            // if neighbor has been visited before i.e it might have an earlier discovery 
            // time given it is not the parent of current node
            else if(visited[neighbor] && parent != neighbor)
                earliest_back_edge[curr] = min(earliest_back_edge[curr], discovery_time[neighbor]);
        }
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // create the graph
        vector<vector<int>> graph(n);
        for(auto edge: connections) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        } 

        // visited[i] = whether ith node is visited or not
        vector<bool> visited(n, false);
        // Order of discovery
        vector<int> discovery_time(n, -1);
        // The earliest known node's discovery time 
        vector<int> earliest_back_edge(n, INT_MAX);

        vector<vector<int>> bridges;
        // Used for assigning the discovery time
        int timer = 1;

        // loop for unvisited nodes
        for(int i = 0; i < n; i++) {
            if(!visited[i])
                findBridges(i, timer, graph, visited, 
                    discovery_time, earliest_back_edge,
                    bridges);
        }

        return bridges;
    }
};
