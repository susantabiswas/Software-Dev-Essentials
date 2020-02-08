/*
    https://leetcode.com/problems/course-schedule/submissions/
*/
class Solution {
public:
    // BFS for detecting cycle
    // TC: O(V + E)
    // The idea is to use Topological sort(Kahn's algo) for detecting cycle.
    // We use the indegree of each node to detect cycle. We traverse according to topological order.
    // If there is a cycle, then the indegree will be 1 more than the actual incoming edges because of a back edge 
    // coming to the vertex. So using BFS we select the vertex with 0 indegree and since 
    // the vertices involved in cycle will have more indegree, they won't be visited at all, 
    // so checking the no. of visited < total vertex means cycle is there.
    bool BFS(int numCourses, vector<vector<int>>& g) {
        // find the indegree
        vector<int> indegree(numCourses, 0);
        for(int i = 0; i < g.size(); i++)
            for(int j = 0; j < g[i].size(); j++)
                ++indegree[g[i][j]];
        
        queue<int> q;
        // push all the vertices of 0 indegree
        for(int i = 0; i < indegree.size(); i++)
            if(indegree[i] == 0)
               q.emplace(i);
        
       // tracks no. of visited vertices
       int visited_vertices = 0;        
        while(!q.empty()) {
            int curr = q.front();
            q.pop();
            ++visited_vertices;
            
            // decrement the indegree of its neighbours
            for(int i = 0; i < g[curr].size(); i++) {
                --indegree[g[curr][i]];
                // add the vertex with 0 indegree
                if(indegree[g[curr][i]] == 0)
                    q.emplace(g[curr][i]);
            }
        }
        
        return visited_vertices < numCourses;
    }
    
    
    // DFS for detecting cycle
    // TC: O(V + E), since entire edge loop runs for each vertex
    // The idea is to detect if there is a back edge from a node to
    // one of nodes in the current branch, so we make the current node as visited
    // and do DFS to go down the branch, if there is a back edge leading to a node 
    // in the current branch then a cycle is detected
    bool dfsCycle(int curr, vector<bool>& visited, vector<vector<int>>& g) {
        // mark the current as visited
        visited[curr] = true;
        
        for(int i = 0; i < g[curr].size(); i++) {
            // if the neighbour is already visited, cycle is there
            if(visited[g[curr][i]])
                return true;
            if(dfsCycle(g[curr][i], visited, g))
                return true;
        }
        
        // make the current node as unvisited, because at a time we need
        // to keep track of nodes in the same branch only
        visited[curr] = false;
        return false;
    }
    
    // DFS driver
    // TC: O(V + E)
    bool DFS(int numCourses, vector<vector<int>>& g) {
        // to keep track of visited courses
        vector<bool> visited(numCourses, false);
        // check if a cycle is there or not, we start DFS from each
        // vertex in case the graph is disconnected
        for(int i = 0; i < numCourses; i++)
            if(!visited[i] && dfsCycle(i, visited, g))
                return false;
        return true;
    }
    
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // make edges for each vertex
        vector<vector<int>> g(numCourses);
        for(auto& edge: prerequisites) 
            g[edge[0]].emplace_back(edge[1]);
        
        // using DFS
        //return DFS(numCourses, g);
        
        // using BFS
        return !BFS(numCourses, g);
    }
};
