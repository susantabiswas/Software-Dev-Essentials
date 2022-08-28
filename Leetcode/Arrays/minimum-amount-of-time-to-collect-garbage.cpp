/*
    https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage/
    
    This is more of a simulation problem. The tricky part is to add the travel time for 
    each of the trucks for the houses where the pickup is needed.
    
    We save the cummulative travel time of going to each house and use this to find out 
    the net travel time needed by each of the trucks for a pickup.
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        // tracks the total time
        int total = 0;
        // last house index where metal/paper/glass was picked
        int last_metal = 0, last_paper = 0, last_glass = 0;
        // travel_time[i] = cummulative travel time till ith house
        vector<long> travel_time(garbage.size(), 0);
        
        for(int house = 0; house < garbage.size(); house++) {
            travel_time[house] = house > 0 ? travel[house - 1] + travel_time[house-1] : 0;
            // whether metal/paper/glass is present
            bool metal = false, paper = false, glass = false;
            
            // Add the time taken for picking up the garbage
            for(auto garbage_type: garbage[house]) {
                if(garbage_type == 'M')
                    metal = true;
                else if(garbage_type == 'P')
                    paper = true;
                else 
                    glass = true;
                
                ++total;
            }
            // If the current house has metal/paper/glass, then the respective truck needs to pick that
            // up. We only add the travel time for a truck if that needs to pickup any garbage at the
            // current house
            if(metal) {
                total += (house > last_metal ? travel_time[house] - travel_time[last_metal] : 0);
                last_metal = house;
            }
            if(paper) {
                total += (house > last_paper ? travel_time[house] - travel_time[last_paper] : 0);
                last_paper = house;
            }
            if(glass) {
                total += (house > last_glass ? travel_time[house] - travel_time[last_glass] : 0);
                last_glass = house;
            }
        }
        
        return total;
    }
};
