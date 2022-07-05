/*
    https://leetcode.com/problems/bus-routes/
    
    TC: O(M + N), M = no. of bus stops, n = no. of buses
    
    Idea is to perform BFS from source bus stop to target bus stop.
    Important thing to think about for this solution is that in BFS we need
    a cost metric that represents each level jump. Here since we have to find the
    min no. of buses, no. of buses is the cost metric we should track while
    transitioning levels in BFS. This also means we can only do curr_num_buses_needed + 1,
    when we use all the info associated with the bus in the current level, only then we can
    say in the next level transition we need one more bus.
    
    To do this, we can do the following:
    - keep a mapping of <bus stop: (buses)>
    - during BFS we use bus stops as nodes and for the edges we add all the
     bus stops that can be traversed from that bus stops. In other words, for a given
     bus stop, we check all the bus stops that connect to that bus stop and then add all
     the bus stops that the bus can take us to. This ensures that we put all the bus stops
     that can be traversed by a bus in the same level and hence would fall under the same 
     curr_num_buses_needed value.
*/
class Solution {
public:
    int bfs(vector<vector<int>>& routes,
            unordered_map<int, unordered_set<int>>& node_to_bus, 
            int source, int target) {
        
        // add all the buses that starts at the source
        // <buses_needed, curr_stop>
        queue<array<int, 2> > q;
        // tracks seen buses and bus stops
        unordered_set<int> visited_stops, visited_buses;
        
        q.push({0, source});
        visited_stops.emplace(source);
        
        // Idea is to perform BFS with no. of buses as the cost
        // between each level. To do so, it is essential we add all the 
        // locations accessible by the given bus in the same level itself
        while(!q.empty()) {
            auto [buses_req, curr_stop] = q.front();
            q.pop();
            
            if(curr_stop == target) 
                return buses_req;
            
            // explore the all the stops accessible from current stop via buses
            for(auto bus: node_to_bus[curr_stop]) {
                if(visited_buses.count(bus))
                    continue;
                for(auto bus_stop: routes[bus]) {
                    // This bus stop can't be reached with current bus, so 
                    // we would need +1 bus
                    if(!visited_stops.count(bus_stop)) {
                        q.push({buses_req + 1, bus_stop});
                        visited_stops.emplace(bus_stop);
                    }
                }
                visited_buses.emplace(bus);
            }
        }
        return -1;
    }
    
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        // <bus_stop, setOf(buses)>
        // For each bus stop, maps all the buses that travels there
        unordered_map<int, unordered_set<int>> node_to_bus;
        
        // For each of the stops, add the buses that travel from there
        for(int bus = 0; bus < routes.size(); bus++) {
            // iterate through the stops, and for each
            // bus stop add the corresponding bus that travels there
            for(int stop = 0; stop < routes[bus].size(); stop++) {
                node_to_bus[routes[bus][stop]].emplace(bus);
            }
        }

        return bfs(routes, node_to_bus, source, target);
    }
};
