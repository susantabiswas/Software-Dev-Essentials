/*
    https://leetcode.com/problems/cheapest-flights-within-k-stops/
    
    Soluion 1
    TC: O(ElogE), looking at the solution carefully, we don't repeat an edge
    because on repeating either of cost or price increases and isn't added to heap.
    SC: O(E)
    
    At a glance this seems like a typical djikstra problem. But there is a 
    caveat here, in a typical djikstra we skip a value if it is stale / outdated
    wrt to cost function.
    In this problem we have two costs: price and stops, price necessarily doesnt
    have priority over costs, since a path might be picked that has better price but ultimately
    goes over K stops and at that point we might not be able to use that path.
    
    [0]--1-->[1]--1-->[2]--1-->[3]
    |                   ^ 
    |___________5_______|
    k = 1
    
    2 has two paths: [0, 1, 2], cost=2, stops=1 and [0, 2], cost=5, stops = 0
    Now price wise if 1st path is picked, stops becomes = 1 and we wont be able to reach [3]
    
    Solution is to allow any path that has either a better stops or price value.
    
    Solution 2: Bellman Ford
    
    Bellman ford modified variant is used. Here for each iteration we take the values
    computed till the last hop, this avoids more hops being used in the current iteration that
    can lead to lower dist.
*/
class Solution {
public:
    int djikstraCost(int src, int dst, unordered_map<int, vector<pair<int, int> > >& g, int k) {
        // <price, stops, node>
        auto comp = [&](const array<int, 3>& a, const array<int, 3>& b) { 
            return a[0] > b[0] || (a[0] == b[0] && a[1] >= b[1]); 
        };
        priority_queue<array<int, 3>, vector<array<int, 3>>, decltype(comp)> min_heap(comp);
        // <node, <price, stops>>
        // Initially all will have INF values for price and stops
        unordered_map<int, pair<int, int>> cost;
        for(auto [node, neighbors]: g)
            cost[node] = {INT_MAX, INT_MAX};
        
        cost[src] = {0, 0};
        // start source will have 0 price and stops
        min_heap.push({0, 0, src});
        
        while(!min_heap.empty()) {
            auto [price, stops, curr] = min_heap.top();
            min_heap.pop();
            
            // target reached
            if(curr == dst && stops - 1 <= k)
                return price;
            
            for(auto [neighbor, flight_price]: g[curr]) {
                // only try the neighbor iff we can get a smaller value for either
                // stops or price
                if(stops - 1 <= k && cost[neighbor].first > price + flight_price || 
                   (cost[neighbor].second > stops + 1)) {
                    
                    cost[neighbor] = {price + flight_price, stops + 1};
                    min_heap.push({price + flight_price, stops + 1, neighbor});
                }
            }
        }
        return -1;
    }
    
    // TC: O(kE)
    // SC: O(n), n = no. of nodes
    int bellmanFord(int n, int src, int dst, vector<vector<int>>& flights, int k) {
        // distance till previous no. of hops
        vector<int> prev(n, INT_MAX);
        prev[src] = 0;
        
        for(int i = 0; i <= k; i++) {
            // distance with curr hop
            vector<int> curr(prev);
            for(auto flight: flights) {
                // the curr dist value depends on the previous min dist data 
                // and so if we find a better dist, that means we are doing +1 hop
                // over the last iteration
                curr[flight[1]] = min(curr[flight[1]], 
                                      prev[flight[0]] == INT_MAX ? INT_MAX : prev[flight[0]] + flight[2]);
            }
            // make the distances with k hops as prev for the next iteration
            prev = move(curr);
        }
        return prev[dst] == INT_MAX ? -1 : prev[dst];
    }
    
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // create the graph
        // <node, [<neighbor, cost>] >
        unordered_map<int, vector<pair<int, int> > > g;
        for(int i = 0; i < n; i++)
            g[i] = vector<pair<int, int>>{};
        
        for(auto flight: flights) 
            // add the edge with cost
            g[flight[0]].emplace_back(make_pair(flight[1], flight[2]));
        
        // return djikstraCost(src, dst, g, k);
        return bellmanFord(n, src, dst, flights, k);
    }
};
