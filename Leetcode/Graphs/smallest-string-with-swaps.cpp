/*
    https://leetcode.com/problems/smallest-string-with-swaps/
    
    Looking at the problem, it seems the way that the way to arrange
    the chars in lexographically smallest order is first know the chain of
    connected nodes. Once we know the chain of connected nodes, we just need to
    put them in sorted order. This ensures that swapping unlimited time to get 
    the smallest lexographical string is done.
    
    TC: O(VlogV + V + E)
*/
class Solution {
public:
    void dfs(int curr, vector<vector<int>>& g, string& s,
             vector<bool>& visited,
             vector<int>& indices, string& elements) {
        
        if(visited[curr])
            return;
        // make visited, add the index and char to respective lists
        visited[curr] = true;
        elements += s[curr];
        indices.emplace_back(curr);
        
        // continue dfs with neighbouring nodes
        for(int neighbour: g[curr])
            if(!visited[neighbour])
                dfs(neighbour, g, s, visited, indices, elements);
    }
    
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        vector<vector<int>> g(s.size());
        // create an adjacency graph
        for(auto edge: pairs) {
            g[edge[0]].emplace_back(edge[1]);
            g[edge[1]].emplace_back(edge[0]);
        }
        
        vector<bool> visited(s.size(), false);
        // for each of the nodes, find out all the connected nodes
        // During dfs keep save the indices and node elements of connected
        // nodes. Once we have the nodes, we can sort the indices and node chars
        // so that we can place the chars lexographically
        for(int v = 0; v < s.size(); v++) {
            if(!visited[v]) {
                vector<int> indices;
                string elements;
                
                dfs(v, g, s, visited, indices, elements);    
                // sort the connected node labels
                sort(elements.begin(), elements.end());
                sort(indices.begin(), indices.end());
                
                for(int i = 0; i < indices.size(); i++)
                    s[indices[i]] = elements[i];
            }
        }
        return s;
    }
}; 
