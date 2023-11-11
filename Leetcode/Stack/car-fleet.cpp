/*
  https://leetcode.com/problems/car-fleet/

  SOLUTION 1: STACK
  A faster car will eventually catch the slower car in front if the ETA for faster one
  is before the slower one and then they will form a fleet.
  So we calculate the ETA for all the cars from left to right and use a monotonically decreasing stack
  to track the eta timings.
  If the current eta >= previous, then that means previous fleet will be forced to join this slower car,
  but if current eta < previous, then previous fleet won't be able to catch up to the current car.
  
  TC: O(nlogn + n) ~ O(nlogn)
  SC: O(n)

  SOLUTION 2: Ordered Set
  TC: O(nlogn + n) [Tree insertion + eta calculation traversal] ~ O(nlogn)
  SC: O(n)
*/
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        // sort the cars by position
        vector<array<int, 2>> cars;
        
        for(int i = 0; i < speed.size(); i++)
            cars.push_back({position[i], speed[i]});
        
        sort(cars.begin(), cars.end());
        
        // Tracks the ETA of cars
        stack<double> eta;
        
        for(auto [position, speed]: cars) {
            // eta for current car
            double t = (double)(target - position) / speed;
            
            // if current car's ETA is slower or equal to the last
            // car, then they will form a fleet
            while(!eta.empty() && t >= eta.top())
                eta.pop();
            eta.push(t);
        }
        return eta.size();
    }
};

// SOLUTION 2
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        // sort the cars wrt to their position (ascending)
        map<int, int> cars;
        for(int i = 0; i < position.size(); i++)
            cars[position[i]] = speed[i];
        
        // now if compute the time it takes for each car to reach the target,
        // we can use that info to see how many cars can catch up and join fleets
        // Eg 1st car(from right) can't catch up to anyone and hence it's a fleet of 1.
        // If 2nd car can reach before 1st, then it can join 1st car's fleet otherwise if it takes
        // longer then it creates a fleet of size 1. Again 3rd one if it can reach faster than 2nd, then it can join 2nd's fleet
        // and so on
        int fleets = 0;
        double max_time_to_reach = 0;
        
        for(auto it = cars.rbegin(); it != cars.rend(); it++) {
            int pos = it->first, speed = it->second;
            double time_to_reach = (double)(target - pos) / speed;
            if(time_to_reach > max_time_to_reach)
                ++fleets, max_time_to_reach = time_to_reach;
        }
        return fleets;
    }
};
