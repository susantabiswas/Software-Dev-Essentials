/*
    https://leetcode.com/problems/car-fleet/
    
    TC: O(NlogN)
    SC: O(N)
*/
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        // sort the cars wrt to their position (ascending)
        // for each car, compute its time to reach the target
        // <position, time_to_reach_target>
        map<int, double> cars;
        for(int i = 0; i < position.size(); i++)
            cars[position[i]] = (double) (target - position[i]) / speed[i];
        
        // now if compute the time it takes for each car to reach the target,
        // we can use that info to see how many cars can catch up and join fleets
        // Eg 1st car(from right) can't catch up to anyone and hence it's a fleet of 1.
        // If 2nd car can reach before 1st, then it can join 1st car's fleet otherwise if it takes
        // longer then it creates a fleet of size 1. Again 3rd one if it can reach faster than 2nd, then it can join 2nd's fleet
        // and so on
        int fleets = 0;
        double max_time_to_reach = 0;
        
        for(auto it = cars.rbegin(); it != cars.rend(); it++) {
            if(it->second > max_time_to_reach)
                ++fleets, max_time_to_reach = it->second;
        }
        return fleets;
    }
};
