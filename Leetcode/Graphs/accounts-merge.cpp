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


//////////////////////////////// Union-Find
// TC: O(n) (Graph creation) + O(nlogm) (Union) + O(mlogm) (Sorting the emails)
// n = total emails, m = unique emails
class Solution {
private:
    class UnionFind {
    public:
        vector<int> root, size;
        
        UnionFind(int n) {
            root.resize(n), size.resize(n, 1);
            for(int i = 0; i < n; i++)
                root[i] = i;
        }
        
        int getRoot(int idx) {
            while(idx != root[idx]) {
                root[idx] = root[root[idx]];
                idx = root[idx];
            }
            return idx;
        }
        
        bool Union(int a, int b) {
            int rootA = getRoot(a);
            int rootB = getRoot(b);
            
            if(rootA != rootB) {
                if(size[rootA] > size[rootB]) {
                    size[rootA] += size[rootB];
                    root[rootB] = rootA;
                }
                else {
                    size[rootB] += size[rootA];
                    root[rootA] = rootB;
                }
                return true;
            }
            return false;
        }
    };
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        // create the graph
        // save the email -> name mapping
        unordered_map<string, string> emailToName;
        unordered_map<string, vector<string>> g;
        unordered_map<string, int> nodeMap;
        int idx = 0;
        
        for(auto account: accounts) {
            string name = account[0], start = account[1];
            
            if(!g.count(start)) {
                emailToName[start] = name;
                g[start] = {};
                nodeMap[start] = idx++;
            }
            
            for(int i = 1; i < account.size(); i++) {
                string email = account[i];
                
                if(!g.count(email)) {
                    emailToName[email] = name;
                    g[email] = {};
                    nodeMap[email] = idx++;
                }    
                g[start].push_back(email);
                g[email].push_back(start);
            }
        }
        
        vector<vector<string>> result;
        unordered_set<string> visited;
        
        UnionFind uf(idx);
        
        for(auto account: accounts) {
            string name = account[0], start = account[1];
            
            if(!g.count(start)) {
                emailToName[start] = name;
                g[start] = {};
                nodeMap[start] = idx++;
            }
            
            for(int i = 1; i < account.size(); i++) {
                string email = account[i];
                
                if(!g.count(email)) {
                    emailToName[email] = name;
                    g[email] = {};
                    nodeMap[email] = idx++;
                }    
                uf.Union(nodeMap[start], nodeMap[email]);
            }
        }
        
        unordered_map<int, vector<string>> allEmails;
        for(auto [email, _]: g)
            allEmails[uf.getRoot(nodeMap[email])].push_back(email);

        for(auto [i, emails]: allEmails) {
            sort(emails.begin(), emails.end());
            string name = emailToName[emails[0]];
            emails.insert(emails.begin(), name);
            result.push_back(emails);
        }
        return result;
    }
};
