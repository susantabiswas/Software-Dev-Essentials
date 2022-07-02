/*
    https://leetcode.com/problems/path-with-maximum-probability/
    
    We use the shortest path algorithms and modify them to give us the max probability path.
    Instead of picking and priortizing smallest weight, we give priority to bigger weight.
*/
class Solution {
public:
    // SOLUTION 1: Bellman Ford
    // TC: O(VE) => TLE
    double bellmanFord(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        // Probability from start node to ith node
        vector<double> prob(n, 0);
        prob[start] = 1.;
        
        // Do relaxation and find the max probability path from start to end via different edges
        for(int i = 0; i < n-1; i++)
            for(int j = 0; j < edges.size(); j++) {
                int src = edges[j][0], dst = edges[j][1];
                // update both src -> dst relation since this is an undirected graph
                // and if we just update according to edge[src, dst], then that be like dealing with 
                // a directed graph
                prob[dst] = max(prob[dst], prob[src] * succProb[j]);
                prob[src] = max(prob[src], prob[dst] * succProb[j]);
            }   
        
        return prob[end];
    }
    
    // SOLUTION 2: Djikstra
    // TC: O(ElogE)
    double djikstraSol(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        // <src, <dst, probability> >
        unordered_map<int, unordered_map<int, double> > graph;
        vector<double> prob(n, 0.0L);
        // create the graph
        for(int i = 0; i < edges.size(); i++) {
            int src = edges[i][0], dst = edges[i][1];
            graph[src][dst] = succProb[i];
            graph[dst][src] = succProb[i];
        }
        // start to start probability is 1
        prob[start] = 1.0L;
        
        auto comp = [&](const pair<double, int>& a, const pair<double, int>& b) { return a.first < b.first; };
        // Max heap based on the probability value
        // <probability, node>
        priority_queue<pair<double, int>, vector<pair<double, int>>, decltype(comp)> max_heap(comp);
        
        max_heap.emplace(make_pair(1., start));
        
        while(!max_heap.empty()) {
            auto curr = max_heap.top();
            double p = curr.first;
            int node = curr.second;
            max_heap.pop();
            
            // target reached
            if(node == end)
                return p;
            
            // stale value
            if(p < prob[node])
                continue;
            
            // unvisited neighbors
            for(auto edge: graph[node]) {
                int dst = edge.first;
                double edge_prob = edge.second;
                // update the probability of reaching the destination node via this node
                if(prob[dst] < prob[node] * edge_prob) {
                    prob[dst] = prob[node] * edge_prob;
                    max_heap.emplace(make_pair(prob[dst], dst));
                }
            }
        }
        return 0;
    }
    
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        // return bellmanFord(n, edges, succProb, start, end);
        return djikstraSol(n, edges, succProb, start, end);
    }
};
