/*
    https://leetcode.com/problems/employee-importance/
    
    Idea is to do graph traversal from id node and explore its neighbors, while
    doing so keep adding the importance score.
    TC: O(V + E)
    SC: O(V)
*/

/*
// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
*/

class Solution {
public:
    int dfs(int curr, unordered_map<int, int>& emp_idx,
           unordered_set<int>& visited, vector<Employee*>& employees) {
        if(visited.count(curr))
            return 0;
        
        // mark as visited
        visited.emplace(curr);
        
        int importance = employees[emp_idx[curr]]->importance;
        for(auto neighbor: employees[emp_idx[curr]]->subordinates)
            importance += dfs(neighbor, emp_idx, visited, employees);
        return importance;
    }
    
    int getImportance(vector<Employee*> employees, int id) {
        // For mapping the node id with the position in vector
        // < node, node_ix>
        unordered_map<int, int> emp_idx;
        unordered_set<int> visited;
        
        for(int i = 0; i < employees.size(); i++) 
            emp_idx[employees[i]->id] = i;
        
        return dfs(id, emp_idx, visited, employees);
    }
};
