/*
    https://leetcode.com/problems/accounts-merge/
    
    Idea is simple, consider the email ids as undirected graph nodes.
    For a given username, we add all the email ids from 2nd as the neighbor of
    the 1st email id. 
    We maintain a mapping of email id: username using a hash table
    Perform DFS on the graph nodes to find out the connected nodes (email ids)
    and use the username mapping to find the username for that connected component.
    
    TC: O(V + E)
*/
class Solution {
public:
    void dfs(string curr, unordered_map<string, vector<string>>& graph,
            unordered_set<string>& visited, vector<string>& data) {
        if(visited.count(curr))
            return;
        // mark as visited
        visited.emplace(curr);
        data.emplace_back(curr);
        
        for(auto neighbor: graph[curr]) 
            if(!visited.count(neighbor))
                dfs(neighbor, graph, visited, data);
    }
    
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, vector<string> > graph;
        // <email, name>
        unordered_map<string, string> name;
        
        for(int i = 0; i < accounts.size(); i++) {
            // 1st entry is name, its saved for tracking purpose
            // 2nd email is taken as the vertex
            name[accounts[i][1]] = accounts[i][0];
            string vertex = accounts[i][1];
            
            if(!graph.count(vertex))
                graph[vertex] = {};
            
            for(int j = 2; j < accounts[i].size(); j++) {
                graph[vertex].emplace_back(accounts[i][j]);
                if(!graph.count(accounts[i][j]))
                    name[accounts[i][j]] = accounts[i][0];
                graph[accounts[i][j]].emplace_back(vertex);    
            }
        }
            
            
        vector<vector<string>> result;
        unordered_set<string> visited;
        
        for(auto [node, neighbors]: graph) {
            // unvisited component, add the Name for this
            // email cluster
            if(!visited.count(node)) {
                // add the name
                vector<string> data = { name[node] };
                // using dfs, find the other connected emails for the
                // given username
                dfs(node, graph, visited, data);
                sort(data.begin() + 1, data.end());
                result.emplace_back(data);
            }
        }
        return result;
    }
};
