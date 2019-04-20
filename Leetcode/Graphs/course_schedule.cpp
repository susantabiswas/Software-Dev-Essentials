/*
    We just have to find whether there is a cycle in the prerequisites graph.
    If cycle is there then not possible else possible.
    
    https://leetcode.com/problems/course-schedule/submissions/
    
    BFS solution:
    1.First compute indegree of each node
    2.Then we start with the nodes with 0 indegree, meaning they dont depend on anybody,
        If there are no such nodes and graph.size() > 0, it has a cycle.
    3.Then we start BFS and each time decrease the degree of its neighbors by 1, indicating we are
        removing the current node's dependency from its neighbor, again look for 0 degree node
        in that level, iif there are none and still there are nodes to travel, cycle is present
        
*/

class Solution {
public:
    // computes indegree of nodes
    vector<int> computeIndegrees(vector<vector<int> >& g) {
        vector<int> indegrees(g.size(), 0);
        for(const vector<int>& l: g) {
            for(const int& v: l)
                ++indegrees[v];
        }    
        
        return indegrees;
    }
    
    bool coursesPossible(vector<vector<int> >& g, vector<int>& indegrees) {
        queue<int> q;
        // push all 0 degree nodes
        for(int i = 0; i < indegrees.size(); i++)
            if(indegrees[i] == 0)
                q.emplace(i);

        // total no. of nodes
        int N = indegrees.size();
        
        // if there were no 0 degree nodes, not possible
        if(q.empty() && N > 0)
            return false;
        // Do BFS of graph 
        while(!q.empty()) {
            int curr = q.front();
            q.pop();
            --N;
            
            // decrement the degree of all its neighbors
            for(const int& v: g[curr]) {
                --indegrees[v];
                if(indegrees[v] == 0)
                    q.emplace(v);
            }
            // if there are still nodes left but 0 indegree nodes, means cycle is present
            if(q.empty() && N > 0)
                return false;
        }
        return true;    
    }
    
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        if(prerequisites.empty())
            return true;
        vector<vector<int> > g(numCourses);
        
        // create a graph
        for(pair<int, int>& edge: prerequisites) {
            g[edge.second].emplace_back(edge.first);
        }
        
       // compute the indegree 
        vector<int> indegree = computeIndegrees(g);
        return coursesPossible(g, indegree);
    }
};

/*
    DFS SOLUTION
    We just have to find whether there is a cycle in the prerequisites graph.
    If cycle is there then not possible else possible.
    
    https://leetcode.com/problems/course-schedule/submissions/
*/

class Solution {
public:
    bool coursesPossible(int curr, vector<vector<int> >& g, vector<int> rec_stack,
                        vector<bool>& visited) {
        // mark current as visited
        visited[curr] = true;
        
        // add to recursion stack
        rec_stack[curr] = true;
        
        for(int v: g[curr]) {
            // check for cycle
            if(rec_stack[v] == true)
                return false;
            if(visited[v] == false)
                if(coursesPossible(v, g, rec_stack, visited) == false)
                    return false;
        }
        rec_stack[curr] = false;
        return true;
    }
    
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        if(prerequisites.empty())
            return true;
        vector<vector<int> > g(numCourses);
        
        // create a graph
        for(pair<int, int>& edge: prerequisites) {
            g[edge.second].emplace_back(edge.first);
        }
        
        // for keeping track of visited nodes
        vector<bool> visited(numCourses, false);
        // for keeping track of nodes in current path, helps to find cycle
        vector<int> rec_stack(numCourses, false);

        for(int i = 0; i < numCourses; i++) {
            bool res;
            if(visited[i] == false)
                res = coursesPossible(i, g, rec_stack, visited);
            
            // if cycle is there, not possible
            if(res == false)
                return false;
        }
        return true;
    }
};
