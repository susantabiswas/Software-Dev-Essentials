/*
    https://leetcode.com/problems/flower-planting-with-no-adjacent/submissions/
    
    Since none of the nodes have more than 3 neighbors, we can select the 
    color not used by the neighbors.

    TC: O(3*N) ~ O(N)    
*/
class Solution {
public:
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
        
        return colorGraph(g);
    }
};
