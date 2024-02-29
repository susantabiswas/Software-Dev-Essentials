/*
    https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
    
    TC: O(log(INT_MAX))
    SC: O(1)
    
    Idea is to find the min weight capacity of the ship using binary search.
    The search space is [0, sum of all the weights], worst case is when we have
    to ship all the packages in 1 day.
    
    We use a boolean predicate function that checks if it is possible to ship all the
    packages with the current 'mid' weight capacity within 'days' no. of days.
*/
class Solution {
public:
    bool possible(int capacity, vector<int>& weights, int days) {
        int req = 0;
        
        int i = 0;
        while(i < weights.size()) {
            long weight = 0;
            
            // add package till we fill the current container
            while(i < weights.size() && weight + weights[i] <= capacity) {
                weight += weights[i];
                ++i;
            }
            
            // if the weight of the package is bigger than the total capacity,
            // it is impossible to ship
            if(i < weights.size() && weights[i] > capacity)
                return false;
            
            ++req;
        }
        
        return req <= days;
    }
    
    int shipWithinDays(vector<int>& weights, int days) {
        int low = 0, high = accumulate(weights.begin(), weights.end(), 0l);
        
        while(low < high) {
            int mid = low + (high - low) / 2;
            
            if(possible(mid, weights, days))
                high = mid;
            else
                low = mid + 1;
        }
        
        return high;
    }
};
