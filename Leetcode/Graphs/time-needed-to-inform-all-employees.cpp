/*
    https://leetcode.com/problems/time-needed-to-inform-all-employees/

    Time needed to inform all the employees is decided by the longest time it takes
    to reach an employee. Since the reporting hierarchy is a tree, we can create a graph
    with the given info and perform BFS.
    Idea is percolate the elapsed time for each employee down the traversal path, while 
    keeping track of max time elapsed so far.

    TC: O(n)
    SC: O(n)
*/
class Solution {
public:
    // Solution 1: BFS
    // TC: O(n)
    // SC: O(n)
    int bfs(int src, vector<vector<int>>& graph, vector<int>& informTime) {
        // <EmpId, Time elapsed till the point this emp was informed>
        queue<pair<int, int> > q;
        q.push({src, 0});

        int max_time_needed = 0;
        
        while(!q.empty()) {
            auto [curr, time_elapsed] = q.front();
            q.pop();

            // For the subordinates of current employees,
            // add the time taken for them to know about about the news
            for(auto neighbor: graph[curr])
                q.push({ neighbor, time_elapsed + informTime[curr] });

            max_time_needed = max(max_time_needed, time_elapsed);
        }
        return max_time_needed;
    }
    
    // Solution 2: DFS
    // TC: O(n)
    // SC: O(n)
    int dfs(int manager, vector<vector<int>>& graph, vector<int>& informTime) {
        int max_elapsed_time = 0;

        for(auto reportee: graph[manager])
            max_elapsed_time = max(max_elapsed_time, dfs(reportee, graph, informTime));
        return max_elapsed_time + informTime[manager];
    }

    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        // create a directed graph, undirected graph is not
        // needed as we know the direction of traversal will be from root and
        // it's a tree so no cycle
        vector<vector<int>> graph(n);

        for(int i = 0; i < n; i++)
            if(manager[i] != -1)
                graph[manager[i]].emplace_back(i);
        
        // return bfs(headID, graph, informTime);
        return dfs(headID, graph, informTime);
    }
};
