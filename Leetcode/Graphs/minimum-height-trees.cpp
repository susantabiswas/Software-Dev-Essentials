/*
    https://leetcode.com/problems/minimum-height-trees/
    
    TC: O(V + E)
    SC: O(V)
*/
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // Since we need to find the MHT roots, we can think of it as finding
        // the nodes which are sort of in the middle of the graph and not near
        // the corners. If a node is near a corner and picked as a root
        // then for it the height will include all the nodes which come on the way from
        // another extreme point. Like if a leaf node is picked then height is taken all the 
        // way from root in a normal binary tree, but if we pick a node in level 2 in a 3 level tree
        // then the chances of it having least height decreases, so we need to find the 
        // nodes which lie in a mid point distance of max distance.
        //            1
        //         2     3
        //        4  5  6 7,     if 4,5,6 or 7 is picked h = 5, 2 and 3 gives h=4, whereas 1 gives h=3 
        
        // find the indegree of each node and use BFS to get to the nodes connected in a central position
        // So naturally it all starts with leaf nodes, remove them in each iteration to get to the central ones
        if(n <= 1)
            return n == 0 ? vector<int>{} : vector<int>{0};
        
        vector<int> indegree(n, 0);
        int min_degree = INT_MAX;
        
        // create a graph
        vector<vector<int>> g(n);
        for(auto &edge: edges) {
            g[edge[0]].emplace_back(edge[1]);
            g[edge[1]].emplace_back(edge[0]);
            ++indegree[edge[0]], ++indegree[edge[1]];
        }
        
        vector<int> result;
        queue<int> q;
        unordered_set<int> visited;
        
        // add leaf nodes(indegree 1)
        for(int i = 0; i < n; i++) {
            if(indegree[i] == 1) {
                q.emplace(i);
                visited.emplace(i);
            }
        }
        
        int n_nodes = q.size();
        
        // we return the nodes in the last level
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            --n_nodes;
            // add node of current level
            result.emplace_back(curr);
            
            // remove the connection count for each neighbor
            for(auto v: g[curr]) {
                if(!visited.count(v)) {
                    --indegree[v];
                    // it has become a leaf node, add and mark visited
                    if(indegree[v] == 1) {
                        q.emplace(v);
                        visited.emplace(v);
                    }
                }
            }
            
            // end of level
            if(n_nodes == 0) {
                // not the last level
                if(!q.empty())
                    result.clear();
                n_nodes = q.size();
            }
        }
        
        return result;
    }
};
