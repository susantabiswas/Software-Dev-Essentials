/*
    https://leetcode.com/problems/parallel-courses/
    
    Each set of prereq course takes one semester. Model all the courses as graph nodes. Then do BFS level by level. Each level contains prereq courses for the next level. At the end return the level.
    TC: O(V + E)
    SC: O(V + E)
*/
class Solution {
public:
    int kahnSol(int n, vector<vector<int>>& relations) {
        vector<int> indegree(n, 0);
        vector<vector<int>> graph(n);
        
        // create the graph and indegree info
        for(auto relation: relations) {
            int src = relation[0] - 1, dst = relation[1] - 1;
            ++indegree[dst];
            graph[src].emplace_back(dst);
        }
        
        queue<int> q;
        // pick the courses with 0 indegree, these are the starting prereq
        for(int node = 0; node < n; node++)
            if(indegree[node] == 0)
                q.emplace(node);
        
        // tracks the level in the BFS traversal
        int level = 1, n_node = q.size();
        int nodes_processed = 0;
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            --n_node;
            ++nodes_processed;
            
            // remove the dependency of this course
            for(auto dst: graph[curr]) {
                --indegree[dst];
                if(indegree[dst] == 0)
                    q.emplace(dst);
            }
            // end of level
            if(n_node == 0 && q.size()) {
                n_node = q.size();
                ++level;
            }
        }
        return nodes_processed == n ? level : -1;
    }
    
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        return kahnSol(n, relations);
    }
};
