/*
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
