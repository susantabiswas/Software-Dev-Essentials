/*
    https://leetcode.com/problems/course-schedule-iv/submissions/
    
    We create a directed graph using the prerequisite edges and each query is basically finding
    a possible path from u to v. So we use dfs to check for a possible path.
*/

class Solution {
private:
    
public:
    // TC: O(N + E)
    bool dfs(int curr, int end, vector<vector<int>>&edges, vector<bool>& visited) {
        if(curr == end)
            return true;
        // mark as visited
        visited[curr] = true;
        
        for(int i = 0; i < edges[curr].size(); i++) {
            if(!visited[edges[curr][i]] && dfs(edges[curr][i], end, edges, visited))
                return true;
                
        }
        return false;
    }
    
    // TC: O(E) + O(q*(N+E)), q: No. of queries
    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        // create a graph
        vector<vector<int>> edges(n);
        for(auto edge: prerequisites)
            edges[edge[0]].emplace_back(edge[1]);
        
        vector<bool> result;
        for(int i = 0; i < queries.size(); i++) {
            vector<bool> visited(n, false);
            result.emplace_back(dfs(queries[i][0], queries[i][1], edges, visited));
        }
        return result;
        
    }
};
