/*
    https://leetcode.com/problems/flower-planting-with-no-adjacent/submissions/
    
    Solution :Greedy
    Since none of the nodes have more than 3 neighbors, we can select the 
    color not used by the neighbors.

    TC: O(3*N) ~ O(N)
    
    Solution: BFS
    TC: O(N)
*/
class Solution {
public:
    // Solution : BFS
    // TC: O(n)
    // SC: O(n)
    // Idea is to assign the 1st node of the component with color 1 and from there 
    // assign the next nodes the next lexographical color. For a given node, its neighbor
    // might be already colored, in that scenario, assign the next color of current node to it.
    vector<int> bfs(int n, vector<vector<int>>& graph) {
        // node_color[i] = color of ith node
        vector<int> node_color(n, -1);
        
        for(int node = 0; node < n; node++) {
            // unprocessed node and start of a new component
            if(node_color[node] == -1) {
                queue<int> q;
                q.push(node);
                // assign 1 to the initial node
                node_color[node] = 1;
                
                while(!q.empty()) {
                    auto curr = q.front();
                    q.pop();

                    for(auto neighbor: graph[curr]) {
                        // if neighbor is uncolored, give the next lexographical color
                        if(node_color[neighbor] == -1) {
                            // % operator will give 0 as the next color of 4, so max of 1 ensures a valid color
                            node_color[neighbor] = max(1, (node_color[curr] + 1) % 5);
                            q.push(neighbor);
                        }
                        // if the neighbor already has the same color, assign it the next color
                        else if(node_color[neighbor] == node_color[curr]) {
                            node_color[neighbor] = max(1, (node_color[curr] + 1) % 5);
                        }
                    }
                }
            }
        }
        return node_color;
    }
    
    // Solution: Greedy
    // TC: O(N)
    // Graph coloring using greedy approach
    vector<int> colorGraph(vector<vector<int>> g) {
        // -1 indicates uncolored
        vector<int> color(g.size(), -1);
        for(int i = 0; i < g.size(); i++) {
            // To track the colors used by neigbors
            vector<bool> color_used(4, false);
            // mark all used colors
            for(const auto& v: g[i])
                if(color[v] != -1)
                    color_used[color[v]-1] = true;
            // look for the unused color
            for(int c = 0; c < 4; c++)
                if(color_used[c] == false) {
                    color[i] = c + 1;
                    break;
                }
                    
        }
        return color;
    }
    
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
        // create a graph, we use 1 extra node to easily match 1 indexing
        vector<vector<int>> g(N);
        for(const auto& edge: paths) {
            g[edge[0] - 1].emplace_back(edge[1] - 1);
            g[edge[1] - 1].emplace_back(edge[0] - 1);
        }
        
        // return colorGraph(g);
        return bfs(n, g);
    }
};
