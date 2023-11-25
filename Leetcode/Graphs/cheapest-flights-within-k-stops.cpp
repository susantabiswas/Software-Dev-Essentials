/*
    https://leetcode.com/problems/cheapest-flights-within-k-stops/
    
    Soluion 1
    TC: O(K * Elog(E * k)), looking at the solution carefully, we don't repeat an edge
    because on repeating either of cost or price increases and isn't added to heap.
    SC: O(E * K)

    The reason there can be EK edges in the heap is because we have 2 criterias for adding an edge.
    It is possible to have an edge with the same/different distances but different 'stops' and the 
    there can be possible K stops, hence the edge can be added via these k different 'stop' paths.
                            | d = 5, stop = 1
                            v
      d = 1, stop = 3-----> A -> B
                            ^
                            | d = 4, stop = 2
    K = 4
    Here edge with d=1 will be added since it has the least distance, but also the edges with d=5, d=4 will be added
    since they have stops + 1 < K and also if there was a path with stops=0, that would have been added as well.
    Hence, there can be K*E entries in the heap and they all can be popped 
    hence EK * log(EK)
    "
        Let E be the number of flights and N be number of cities in the given problem.

        Time complexity: O(N + E⋅K⋅log(E⋅K))
            Let's assume any node A is popped out of the queue in an iteration. 
            If the steps taken to visit A are more than stops[node], we do not iterate over the neighbors of A.
            However, we will iterate over neighbors of A if the steps are less than stops[A], 
            which can be true K times. A can be popped the first time with K steps, followed by K-1 steps, 
            and so on until 1 step. The same argument would be valid for any other node like A. As a result, 
            each edge can only be processed KK times, resulting in O(E⋅K) elements being processed.
            It will take the priority queue O(E⋅K⋅log(E⋅K)) time to push or pop O(E⋅K) elements.
            We've added O(N) time by using the stops array.
    
        Space complexity: O(N+E⋅K)
            We are using the adj array, which requires O(E) memory. 
            The stop array would require O(N) memory. As previously stated, the priority queue can only have O(E⋅K) elements.
    "

    
    At a glance this seems like a typical djikstra problem. But there is a 
    caveat here, in a typical djikstra we skip a value if it is stale / outdated
    wrt to cost function.
    In this problem we have two costs: price and stops, price necessarily doesnt
    have priority over stops, since a path might be picked that has better price but ultimately
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
        // As per the question, stops are only the cities that lie in between the
        // source and destination. But to make code easier to understand and write we 
        // can consider the final city also as a stop and thus we can have max allowed K+1 stops.
        k = k + 1;
        
        while(!min_heap.empty()) {
            auto [price, stops, curr] = min_heap.top();
            min_heap.pop();
            
            // target reached
            if(curr == dst && stops <= k)
                return price;

            // The reason why we track the visited node is because our heap operates on the
            // price metric but we allow both the lower price or lower stops for heap addition.
            // Let's say we have added two edges for a node X, one with a lower price and one with
            // lower number of stops. We will get the min price edge first and if we mark the node as 
            // visited, we won't see the lower stops edge, hence we don't track visited nodes.
            
            for(auto [neighbor, flight_price]: g[curr]) {
                // only try the neighbor iff we can get a smaller value for either
                // stops or price
                if(stops + 1 <= k && cost[neighbor].first > price + flight_price || 
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
        
        return djikstraCost(src, dst, g, k);
        // return bellmanFord(n, src, dst, flights, k);
    }
};
