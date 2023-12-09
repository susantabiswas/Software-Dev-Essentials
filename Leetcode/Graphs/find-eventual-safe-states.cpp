/*
    https://leetcode.com/problems/find-eventual-safe-states/
    
    Code Idea is to identify the nodes which are on a cyclic path. Terminal nodes are basically
    non-cyclic path ends. So once we know the nodes from where traversal will end in a cyclic path,
    we can pick the remaining nodes which will be the safe nodes.

    Sol1:
        Idea is to do topological sort to detect cycle, we save the result of this in DP cache so
        that we don;t have to repeat the operation for each and every nodes.

    Sol2:
        Since Terminal nodes are safe, if we had a way to retract the path backward, it would have lead to all
        the safe nodes on that path. So we do that, create a reverse graph where the edge directions are 
        reversed. Then using inorder degree traverse the way backwards.

        BFS with inorder doesnt tarverse cyclic nodes, so one question why not just do BFS with orig graph,
        it should avoid all the cyclic ones. If we do BFS with the original graph, then safe nodes connected to a cycle 
        will also be missed as their degree won't be decremented at all.

    Another Style
        Here we don't start dfs for each of the nodes from the driver, but only start for the nodes unvisited
*/
class Solution {
private:
    enum Color { WHITE, GREY, BLACK };
public:
    //////////////////// SOLUTION 1: TOPOLOGICAL SORT + DP ///////////////////////////
    // TC: O(V + E)
    // SC: O(V)

    // Topological Sort: Returns True if there is a cycle, otherwise false
    // Also added DP cache to save the result for each the processed nodes
    bool topologicalDp(int curr, vector<vector<int>>& graph,
            vector<int>& dp, vector<bool>& visited, vector<bool>& rec_stack) {
        
        if(dp[curr] == -1) {
            // mark it visited
            visited[curr] = true;
            // put the current in recursion stack
            rec_stack[curr] = true;

            // process the neighbors
            for(auto neighbor: graph[curr]) {
                // A node already in the current recursion path found, means a cycle
                if(rec_stack[neighbor])
                    return dp[curr] = 1;
                if(!visited[neighbor] && topologicalDp(neighbor, graph, dp, visited, rec_stack))
                    return dp[curr] = 1;
            }

            // remove the node from recursion path since we are
            // backtracking now
            rec_stack[curr] = false;
            // Had there been a cycle we would have returned the control above itself,
            // since we are here means no cycle
            dp[curr] = 0;
        }
        return dp[curr];
    }

    vector<int> dfsDPSol(vector<vector<int>>& graph) {
        int N = graph.size();
        // dp[i] = <whether the path from here leads to a cycle or not>
        vector<int> dp(N, -1);
        // to track visited nodes
        vector<bool> visited(N, false);
        // Indicates whether ith node is in the current recursion path 
        vector<bool> rec_stack(N, false);
        vector<int> result;

        for(int i = 0; i < N; i++)
            if(!topologicalDp(i, graph, dp, visited, rec_stack))
                result.emplace_back(i);
        return result;
    }

    //////////////////// SOLUTION 2: BFS WITH GRAPH REVERSAL ///////////////////////////
    // TC: O(V + E)
    // SC: O(V)
    vector<int> bfsReversalSol(vector<vector<int>>& graph) {
        vector<int> result;
        int N = graph.size();
        vector<vector<int>> rev_graph(N);

        // create a reverse graph by reversing the edges
        for(int i = 0; i < N; i++)
            for(int neighbor: graph[i])
                rev_graph[neighbor].emplace_back(i);

        // Now perform BFS on the reversed graph. We start with the 
        // terminal nodes and follow the path towards the safe nodes 
        // from there
        queue<int> q;
        // Compute the indegree
        vector<int> indegree(N, 0);
        
        for(int src = 0; src < N; src++)
            for(int dst: rev_graph[src])
                ++indegree[dst];

        // find 0 degree nodes
        for(int src = 0; src < N; src++)
            if(indegree[src] == 0)
                q.emplace(src);
 
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();

            result.emplace_back(curr);

            for(auto neighbor: rev_graph[curr]) {
                --indegree[neighbor];
                if(indegree[neighbor] == 0)
                    q.emplace(neighbor);
            }
        }
        
        sort(result.begin(), result.end());
        return result;
    }

    //////////////////// SOLUTION 3: GRAPH COLORING ///////////////////////////
    // TC: O(V + E)
    // SC: O(V)
    // Retruns true if there is a cycle
    bool dfs(int curr, vector<vector<int>>& graph, vector<Color>& color) {
        // Node already processed
        if(color[curr] != WHITE)
            return color[curr] == GREY;
        
        // Mark it as processing
        color[curr] = GREY;

        // process the neighbors
        for(auto neighbor: graph[curr]) {
            // Node already on the recursion stack
            if(color[neighbor] == GREY)
                return true;
            // Check if a cycle is found at a later stage
            if(color[neighbor] == WHITE && dfs(neighbor, graph, color))
                return true;
        }

        // Processing finished
        color[curr] = BLACK;
        return false;
    }

    vector<int> dfsColorSol(vector<vector<int>>& graph) {
        vector<int> result;
        int N = graph.size();
        
        // Colors to represent the state of nodes.
        // White: Unprocessed node
        // Grey: (Unsafe node) When node is under processing in the current recursion stack.
        //        If node is part of cyclic path, then this state won't change to Black for the current node
        // Black: (Safe Node) When node has finished processing this is assigned
        vector<Color> color(N, WHITE);

        for(int i = 0; i < N; i++) {
            if(!dfs(i, graph, color))
                result.emplace_back(i);
        }
        return result;
    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        // return dfsDPSol(graph);
        // return bfsReversalSol(graph);
        return dfsColorSol(graph);
    }
};

/////////////////////////////////////////// Another Style
class Solution {
public:
    bool dfs(int curr, vector<vector<int>>& g, vector<int>& color, vector<int>& safe) {
        if(color[curr] == 1)
            return false;
        
        // node added to recursion stack
        color[curr] = 0;
        
        for(auto neighbor: g[curr]) {
            if(color[neighbor] == 0)
                return true;
            if(dfs(neighbor, g, color, safe))
                return true;
        }
        
        // node removed from recursion stack
        color[curr] = 1;
        // all the paths from current node ended without a cyclic path
        // so it is safe
        safe.push_back(curr);
        
        return false;
    }
    
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<int> safe;
        
        // -1: unprocessed, 0: processed, 1: processed
        vector<int> color(graph.size(), -1);
        
        for(int node = 0; node < graph.size(); node++)
            if(color[node] == -1)
                dfs(node, graph, color, safe);
        
        sort(safe.begin(), safe.end());
        return safe;
    }
};
