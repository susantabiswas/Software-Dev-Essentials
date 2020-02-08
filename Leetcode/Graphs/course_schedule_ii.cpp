/*
    https://leetcode.com/problems/course-schedule-ii/
    
    The problem is basically to find the topological ordering of graph vertices.
    TC: O(V + E)
*/
class Solution {
public:
    // DFS Helper
    // Returns true in case of cycle else false
    bool topologicalDFS(int curr, vector<vector<int>>& g, vector<int>& order, 
                       vector<bool>& rec_stack, vector<bool>& visited) {
        // current is visited means, topological ordering from current node
        // must already be added, so we can safely ignore the remaining vertices from here on
        if(visited[curr])
            return false;
        // mark the current as visited
        visited[curr] = true;
        // add to recursion stack
        rec_stack[curr] = true;
        
        // DFS for its neighbours
        for(int i = 0; i < g[curr].size(); i++) {
            // if current is already visited, that means there is a cycle
            if(rec_stack[g[curr][i]])
                return true;
            else if(topologicalDFS(g[curr][i], g, order, rec_stack, visited))
                return true;
        }
        // make the current node of branch unvisited
        rec_stack[curr] = false;
        // add the current in the order after processing its neighbours
        order.emplace_back(curr);
        
        return false;
    }
    
    // Using DFS
    // TC: O(V + E)
    vector<int> topologicalDFS(vector<vector<int>>& g) {
        // for tracking visited vertices
        vector<bool> visited(g.size(), false);
        // for keeping track of vertices in recursion stack
        vector<bool> rec_stack(g.size(), false);
        vector<int> order;
        // in case of disconnected graph
        for(int i = 0; i < g.size(); i++)
            if(!visited[i])
                // if there is a cycle return empty order
                if(topologicalDFS(i, g, order, rec_stack, visited))
                    return vector<int>{};
        return order;
    }
    
    // Using BFS
    // TC: O(V + E)
    vector<int> topologicalBFS(vector<vector<int>>& g) {
        vector<int> order;
        // to keep track of visited vertices
        int visited_vertices = 0;
        
        // find the indegree of vertices
        vector<int> indegree(g.size(), 0);
        for(int i = 0; i < g.size(); i++)
            for(int j = 0; j < g[i].size(); j++)
                ++indegree[g[i][j]];
        
        queue<int> q;
        // add the 0 indegree vertices
        for(int i = 0; i < indegree.size(); i++)
            if(indegree[i] == 0)
                q.emplace(i);
        
        while(!q.empty()) {
            int curr = q.front();
            order.emplace_back(curr);
            q.pop();
            ++visited_vertices;
            
            // decrement the indegree of its neighbours
            for(int i = 0; i < g[curr].size(); i++) {
                --indegree[g[curr][i]];
                if(indegree[g[curr][i]] == 0)
                    q.emplace(g[curr][i]);
            }
        }
        
        // return the order in reverse 
        reverse(order.begin(), order.end());
        return visited_vertices < g.size() ? vector<int>{} : order;
    }
    
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // make the graph using the prerequisites info
        vector<vector<int>> g(numCourses);
        for(const auto& v: prerequisites) {
            g[v[0]].emplace_back(v[1]);
        }
        
        // topological sort using DFS
        //vector<int> order = topologicalDFS(g);
        // topological sort using BFS
        vector<int> order = topologicalBFS(g);
        
        return order;
    }
};

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
