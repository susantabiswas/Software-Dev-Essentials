/*
    210. Course Schedule II
    https://leetcode.com/problems/course-schedule-ii/submissions/
    
    Topological sort.
*/
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        int N = numCourses;
        // create graph
        vector<vector<int>> g(N);
        // for storing topological order
        vector<int> order;
        // we will find the topological order using BFS
        // for that we store indegree of each node
        vector<int> indegree(N, 0);
        
        // find the indegree and create the graph
        for(pair<int, int>& edge: prerequisites) {
            g[edge.second].emplace_back(edge.first);
            ++indegree[edge.first];
        }
        
        queue<int> q;
        // start with all 0 degree nodes
        for(int i = 0; i < N; i++)
            if(indegree[i] == 0)
                q.emplace(i);
        
        while(!q.empty()) {
            int curr = q.front();
            q.pop();
            // indicates one element is dealt with
            --N;    
            order.emplace_back(curr);
            // reduce degree by 1 of its neighbors
            // One thing to note is we are not using visited array,
            // because for a already visited node, its indegree = 0, so
            // when we do --indegree it becomes < 0 and never is selected again
            for(const int v: g[curr]) {
                --indegree[v];
                if(indegree[v] == 0)
                    q.emplace(v);
            }
        }
        
        return N == 0 ? order : vector<int>{};
    }
};
