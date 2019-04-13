/*
  Is graph bipartite.
  https://leetcode.com/problems/is-graph-bipartite/
*/

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        
        // try all vertices incase the graph is not connected
        for(int j = 0; j < graph.size(); j++)
        {        
            vector<vector<int> > color(graph.size(), vector<int>(1, -1));
            queue<int> q;

            // add the first vertex
            q.emplace(j);
            // give the vertex a color, we give it 0
            color[j][0] = 0;

            while(!q.empty()) {
                int curr = q.front();
                q.pop();

                // color its adjacent vertices
                for(int i = 0; i < graph[curr].size(); i++) {
                    // if any of its adjacent vertices have the same color,
                    // then it is not bipartite

                    // if the adjacent vertex is not colored
                    if(color[graph[curr][i]][0] == -1) {
                        // give it a different color 
                        color[graph[curr][i]][0] = color[curr][0] == 0 ? 1:0;
                        // add to queue
                        q.emplace(graph[curr][i]);
                    }
                    else {
                        if(color[graph[curr][i]][0] == color[curr][0])
                            return false;
                    }
                }
            }
        }
        return true;
    }
};
