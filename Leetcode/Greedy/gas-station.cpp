/*
    https://leetcode.com/problems/gas-station/
    
    TC: O(n)
    SC: O(1)
    
    Points to note:
    1. We can only cover the path if total fuel > total distance cost
    2. We can only reach a stop if there is >= distance from the previous stop
    3. This means each time we reach a stop, there is a possibility to accumulate surplus fuel. This surplus
        fuel can help cover any extra distance if fuel from the previous stop is not enough
    
    With all the above facts, we can say that if our current fuel requirement to reach the next stop 'i' is negative,
    that means there is no point choosing any stop after the current start till current i-1 stop, as the surplus will
    decrease and will definitely not be able to make to ith stop.
    
    So choose the next stop as the new start point and continue till we reach the n-1 th stop. We dont need to rollover and go till start-1
    because we know there is enough fuel to cover the total distance.
*/
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        long total_gas = accumulate(gas.begin(), gas.end(), 0l);
        long total_cost = accumulate(cost.begin(), cost.end(), 0l);
        
        // if the total fuel is not enough to cover the path, it is 
        // not possible
        if(total_gas - total_cost < 0)
            return -1;
        
        int start = 0, curr = 0;
        int tank = 0;
        
        for(; curr < cost.size(); curr++) {
            // fill the tank and check if travel to next stop is possible 
            tank += gas[curr] - cost[curr];
            
            // The current start point is not the correct choice, 
            // pick the next point as the start
            // Whenever we reach a stop, that means we had a surplus fuel to reach there
            // This means we reached here because of surplus collected from each of the stops before this.
            // So if we pick any stop as the start after the current start, we will still not be able to go past
            // the current stop as the cost req is too high and picking any point after current start will result in lesser surplus only
            if(tank < 0) {
                start = curr + 1;
                tank = 0;
            }
        }
        
        return start;
    }
};
