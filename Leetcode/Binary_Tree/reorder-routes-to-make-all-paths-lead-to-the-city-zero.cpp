/*
    https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/
    
    TC: O(n)
    SC: O(n)
    
    Points to note:
    - There wont be any cycle, so each node pair is connected via that edge only. We just have
    to worry about orienting that edge
    - Since all the nodes should reach the node 0, node 0 can be thought of as a tree and all the
    other nodes form the tree with root node 0
    
    Idea is to start the traversal from node 0, then for all of its neighbors, whichever neighbor's edge is not facing  towards the
    current parent, reverse their orientation and start dfs from that node in a similar manner
    
*/
class Solution {
public:
    void dfs(int curr, int& rev, unordered_map<int, unordered_set<int>>& edges,
            unordered_map<int, unordered_set<int>>& neighbors,
            unordered_set<int>& visited) {
        // already visited
        if(visited.count(curr))
            return;
        
        visited.insert(curr);
        
        for(auto neighbor: neighbors[curr]) {
            // if the neighbor doesnt traverses towards the current node, then
            // reverse the orientation so that neighbor's edge is directed towards current node
            if(!visited.count(neighbor) && !edges[neighbor].count(curr))
                ++rev;
            if(!visited.count(neighbor))
                dfs(neighbor, rev, edges, neighbors, visited);
        }
    }
    
    int minReorder(int n, vector<vector<int>>& connections) {
        // edges: [node, (neighbors which can be reached via the directed edge)]
        // neighbors: [node, (surrounding neighbors, irrespective of direction)]
        unordered_map<int, unordered_set<int>> edges, neighbors;
        unordered_set<int> visited;
        
        // create the mapping of directed edges and surrounding neighbors
        for(auto edge: connections) {
            int src = edge[0], dst = edge[1];
            
            edges[src].insert(dst);
            neighbors[src].insert(dst);
            neighbors[dst].insert(src);
        }
        
        // Start the DFS from source 0 (think of this as tree root) and start
        // percolating downwards in the tree, if the connecting neighbor is not directed towards
        // its parent, then it needs to be reversed
        int rev = 0;
        for(int node = 0; node < n; node++) {
            if(!visited.count(node)) 
                dfs(node, rev, edges, neighbors, visited);
        }
        
        return rev;
    }
};
///////////////////////////////// SOLUTION 2

/*
    https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/submissions/
    
    TC: O(N)
    SC: O(N)
*/

class Solution {
    struct Edge {
        int endpt = -1;
        // whether the edge allows travel to endpt
        bool travel_allowed = true;
        
        Edge(int endpt, bool travel_allowed): 
            endpt(endpt), travel_allowed(travel_allowed) {};
    };
public:
    void dfs(int curr, vector<vector<Edge>>& g,
            unordered_set<int>& visited, int &changes) {
        
        // mark as visited
        visited.emplace(curr);
        
        // DFS with all the neighboring paths
        for(int i = 0; i < g[curr].size(); i++) {
            // if the neighbor is unvisited
            if(visited.count(g[curr][i].endpt) == 0) {
                // if the edge allows travel from current direction only,
                // it needs to be reoriented, since the neighbor won't be able to each 
                // the current node
                if(g[curr][i].travel_allowed)
                    ++changes;
                dfs(g[curr][i].endpt, g, visited, changes);
            }
        }
    }
    
    int minReorder(int n, vector<vector<int>>& connections) {
        // We create a graph, and for two connected nodes
        // add the path for both the nodes. Mark the edge
        // which directly allows travel as 'travel_allowed': true
        // false for the other.
        // Since each node is only connected via one path with the 
        // other node and we can only orient the direction of path,
        // means, we just have to find the edges that can't be used to 
        // travel from root to reach the rest of the nodes
        vector<vector<Edge>> g(n);
        for(auto edge: connections) {
            g[edge[0]].emplace_back(Edge(edge[1], true));
            g[edge[1]].emplace_back(Edge(edge[0], false));
        }
        
        // Do simple DFS to find the edges that doesnt let travel
        unordered_set<int> visited;
        // edge orientations required
        int changes = 0;
        dfs(0, g, visited, changes);
        return changes;
    }
};
