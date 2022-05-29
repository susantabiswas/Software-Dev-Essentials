/*
    https://leetcode.com/problems/network-delay-time/
    
    Sol1: Bellman Ford
        Bellman Ford can be used to find min distance from source to all nodes.
        
    Sol2: Djikstra
        Djikstra is usually used to min dist from src to dst, but if we remove the check
        that stops the process when target is reached, we can compute min dist to all other nodes.
*/
class Solution {
public:
    // Solution1: Bellman Ford
    // TC: O(nE), E = no. of edges
    // SC: O(n)
    int bellmanFord(vector<vector<int>>& times, int n, int k) {
        // delay[i] = time to reach kth node
        vector<int> delay(n+1, INT_MAX);
        // we start from  node kth node as source, all other nodes are destinations
        delay[k] = 0;
        
        for(int i = 0; i < n; i++) {
            for(auto edge: times) {
                // delay[dst] > delay[src] + wt
                delay[edge[1]] = min(delay[edge[1]], 
                                     delay[edge[0]] == INT_MAX ? INT_MAX : delay[edge[0]] + edge[2]);
            }
        }
        // 0th element is dummy, so skip . Find the max delay time, this will decide the overall delay
        int max_delay = *max_element(delay.begin() + 1, delay.end());
        
        return max_delay == INT_MAX ? -1 : max_delay;
    }
    
    // TC: O(ElogE) + O(V+E)
    int djikstra(vector<vector<int>>& times, int n, int k) {
        // create graph, 0th node is dummy
        // node: <dst, time>
        vector<vector<pair<int, int> > > g(n+1);
            
        for(auto edge: times) 
            g[edge[0]].emplace_back(make_pair(edge[1], edge[2]));
        
        // delay[i] = min time to reach kth node
        vector<int> delay(n+1, INT_MAX);
        
        auto comp = [&](const array<int, 2>& a, const array<int, 2>& b) { return a[1] >= b[1]; };    
        // <node, time>
        priority_queue<array<int, 2>, vector<array<int, 2>>, decltype(comp)> min_heap(comp);
        min_heap.push({k, 0});
        // starting dist will be 0
        delay[k] = 0;
        
        while(!min_heap.empty()) {
            auto [curr, curr_time] = min_heap.top();
            min_heap.pop();
            
            if(delay[curr] > curr_time)
                continue;
            
            for(auto [dst, t]: g[curr]) {
                if(delay[dst] > delay[curr] + t) {
                    delay[dst] = delay[curr] + t;
                    min_heap.push({dst, delay[curr] + t});
                }
            }
        }
        
        int max_delay = *max_element(delay.begin() + 1, delay.end());
        return max_delay == INT_MAX ? -1 : max_delay;
    }
    
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // return bellmanFord(times, n, k);
        return djikstra(times, n, k);
    }
};
