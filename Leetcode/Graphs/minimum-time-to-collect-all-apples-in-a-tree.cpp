/*
    https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/submissions/
    
    We make a graph and do DFS to find finding the paths with apples. During DFS we find the
    total one way path length from root till the last apple in subtree. DFS returns whether there is a 
    apple in the current tree or not, if that is true, we include the the parent node to connect it with
    the subtree by adding +1.
    
    TC: O(V + E)
    SC: O(V)
*/

class Solution {
public:
    // TC: O(V + E)
    bool dfs(int curr, vector<vector<int>>& g,
                vector<bool> &has_apple, int& dist,
                unordered_set<int> &visited) {
        
        if(visited.count(curr))
            return false;
        // mark it as visited
        visited.emplace(curr);
        
        for(int &v: g[curr]) {
            // this is passed to the subtree as ref and
            // this stores the length of path in the subtree till the last apple
            // in subtree, 0 otherwise
            int dist_cost = 0;
            // if the subtree has an apple we need to include the current node
            if(dfs(v, g, has_apple, dist_cost, visited))
                dist += dist_cost + 1;
            
        }
        // if atleast a single apple was found in any of the subtree paths
        // or the current node itself has an apple,
        return dist > 0 || has_apple[curr];
    }
    
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        // create a graph
        vector<vector<int>> g(n);
        for(auto edge: edges) {
            g[edge[0]].emplace_back(edge[1]);
            g[edge[1]].emplace_back(edge[0]);
        }
        
        unordered_set<int> visited;
        int dist = 0;
        dfs(0, g, hasApple, dist, visited);
        // perform DFS
        return 2 * dist;
    }
};
