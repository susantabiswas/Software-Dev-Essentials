/*
    https://leetcode.com/problems/build-a-matrix-with-conditions/
    
    TC: O(k + r + c)
    SC: O(k + r + c),
    r = size of rowConditions
    c = size of colConditions
    
    Looking at the conditions, it says we need to ensure that pairs are placed
    appropriately accoridng to the order provided. This is topological sort problem.
    We use topological sort for row and col conditions.
    
    Then once we know the row and col index for each of the 1..k elements, then
    we just need to map each of the elements to their right row and col.
*/
class Solution {
public:
    // Returns true if cycle is present
    bool topologicalSort(int k, unordered_map<int, vector<int>>& graph, vector<int>& order) {
        // tracks the no. of nodes processed
        int processed = 0;
        // indegree of each node
        vector<int> indegree(k, 0);
        queue<int> q;
        
        for(auto [src, neighbors]: graph) 
            for(auto dst: neighbors)
                ++indegree[dst];
        
        // Add the 0 degree nodes
        for(int i = 0; i < indegree.size(); i++) 
            if(indegree[i] == 0)
                q.emplace(i);
            
        while(!q.empty()) {
            auto curr = q.front();
            order.emplace_back(curr);
            ++processed;
            q.pop();
            
            for(auto neighbor: graph[curr]) {
                --indegree[neighbor];
                if(indegree[neighbor] == 0)
                    q.emplace(neighbor);
            }
        }
        // There is a cycle if we are not able to process all the nodes
        return processed < indegree.size();
    }
    
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        // final grid where elements from [1..k] are placed
        vector<vector<int>> grid(k, vector<int>(k, 0));
        
        unordered_map<int, vector<int>> row_graph, col_graph;
        
        // build the graphs for row and col dependencies
        for(auto condition: rowConditions) 
            row_graph[condition[0] - 1].emplace_back(condition[1] - 1);
        for(auto condition: colConditions) 
            col_graph[condition[0] - 1].emplace_back(condition[1] - 1);
        
        // Stores the topological order of row and col elements
        vector<int> row_order, col_order;
        
        // cycle detected 
        if(topologicalSort(k, row_graph, row_order) || 
           topologicalSort(k, col_graph, col_order))
            return {};
        
        // <num, col_position>
        unordered_map<int, int> col_position;
        
        // Stores the mapping between element and its col position
        for(int col = 0; col < k; col++) 
            col_position[col_order[col]] = col;
        
        // Since we know the element for each row, all we have to
        // do is put that element's col position to store the element
        // +1 since elements were stored in 0indexed manner during the above process
        for(int row = 0; row < k; row++) 
            grid[row][col_position[row_order[row]]] = row_order[row] + 1;
            
        return grid;
    }
};
