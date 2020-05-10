/*
  https://leetcode.com/problems/find-the-town-judge/submissions/
*/

// SOLUTION 1
/*
    https://leetcode.com/problems/find-the-town-judge/submissions/
    
    TC: O(N), SC: O(N)
*/
class Solution {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        // We can consider each label as a graph node
        // find the indegree and out degree of each node
        vector<int> indegree(N, 0), outdegree(N, 0);
        for(auto trust_edge: trust) {
            ++indegree[trust_edge[1] - 1];
            ++outdegree[trust_edge[0] - 1];
        }
        
        // now check which node has N-1 indegree and for that node
        // check if its outdegree is also 0, if both cond. are true, then that
        // ndoe is town judge
        for(int i = 0; i < indegree.size(); i++) {
            if(indegree[i] == N-1 && outdegree[i] == 0)
                return i + 1;
        }
        return -1;
    }
};

///////////////////////////////////
// SOLUTION 2
class Solution {
public:
    
    // Normal DFS to check reachability
    void DFS(int v, vector<vector<int> >& adj, vector<bool>& visited) {
        // mark current as visited
        visited[v] = true;
        
        // visit its not visited adjacent neighbours
        for(int i = 0; i < adj[v].size(); i++)
            if(visited[adj[v][i]] == false)
                DFS(adj[v][i], adj, visited);
    }
    /*
        Judge should be able to reach every vertex and there can only be one judge.
        So we do DFS and check if there are more than one source vertex or not, if there are
        then judge can't exist. If we get a judge candidate then check if it has N-1 neighbours
        or not.
    */
    int findJudge(int N, vector<vector<int>>& trust) {
        // construct the graph
        vector<vector<int> > adj(N);
        for(int i = 0; i < trust.size(); i++) {
            //[a, b] : b-->a
            // add the edge
            adj[trust[i][1] - 1].emplace_back(trust[i][0] - 1);
        }
        
        int judge = -1;
        // find the source vertex
        for(int i = 0; i < N; i++) {
            // for tracking visited vertices
            vector<bool> visited(N, false);
            // do DFS and check if current vertex is the source vertex or not
            DFS(i, adj, visited);
            
            bool src = true;
            for(const auto& a: visited)
                if(a == false) {
                    src = false;
                    break;
                }
            // first jusge candidate
            if(judge == -1 && src )
                judge = i + 1; 
            // when another judge candidate is found
            else if(judge != -1 && src) {
                return -1;
            }
        }
        
        // check if candidate is really the judge and has N-1 neighbours
        return judge != -1 && adj[judge-1].size() == N-1 ? judge : -1;
    }
};
