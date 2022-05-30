/*
    https://leetcode.com/problems/evaluate-division/
    
    TC: O(V + E)
    SC: O(V)
    
    To find the division value for a given A/B, when the diff equations are given, we can
    map the equation relations to graph edges and create a graph. 
    For a given A/B = val we create 2 edges : A->B = val and B->A = 1 / val.
    
    Then using a graph traversal algo like dfs or bfs search for the target.
*/
class Solution {
public:
    double bfs(string src, string dst,
               unordered_map<string, unordered_map<string, double> >& graph) {
        // Either / both the src and dst don't have any equation relation
        if(!graph.count(src) || !graph.count(dst))
            return -1.0;
        
        queue<pair<string, double> > q;
        unordered_set<string> visited;
        
        // Start BFS with source node
        q.emplace(make_pair(src, 1.));
        visited.emplace(src);
        
        while(!q.empty()) {
            auto [curr, result] = q.front();
            q.pop();
            
            // if target reached
            if(curr == dst)
                return result;
            
            // process unvisited neighboring variables
            for(auto [neighbor, value]: graph[curr]) {
                // If the neighboring variable is unvisited, use that equation relation
                if(!visited.count(neighbor)) {
                    visited.emplace(neighbor);
                    q.emplace(make_pair(neighbor, result * value));
                }
            }
        }
        
        return -1.0;
    }
    
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int N = equations.size();
        unordered_map<string, unordered_map<string, double> > graph;
        
        // Create a graph for each of the equations a->b = val and b->a = 1/val
        for(int i = 0; i < N; i++) {
            graph[equations[i][0]].emplace(equations[i][1], values[i]);
            graph[equations[i][1]].emplace(equations[i][0], 1.0 / values[i]);
        }
        
        vector<double> result;
        // Use graph traversal to find a way to reach the destination
        for(auto query: queries) {
            result.emplace_back(bfs(query[0], query[1], graph));
        }
        return result;
    }
};
