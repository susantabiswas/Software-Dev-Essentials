/*
    https://leetcode.com/problems/heaters/submissions/
    
    Solution is very similar to Painter's partition problem.
    We do the binary search on the search space for radius.
    For each radius we check if all the houses can be covered or not,
    if it can be covered, we try to look for the smallest radius that can cover it.
    
    
    TC: for sorting the arrays: O(mlogm + nlogn)
        for doing binary search O(nlog(INT_MAX))
*/

class Solution {
public:
    // Checks if with the given radius all the houses can be covered or not
    bool housesCovered(vector<int> houses, vector<int>& heaters,
                       int radius) {
        int left = heaters[0] - radius;
        int right = heaters[0] + radius;
        int heater_idx = 0, house_idx = 0;
        
        while(house_idx < houses.size()) {
            if(houses[house_idx] >= left && houses[house_idx] <= right) {
                ++house_idx;
            }
            else {
                ++heater_idx;
                if(heater_idx == heaters.size())
                    return false;
                left = heaters[heater_idx] - radius;
                right = heaters[heater_idx] + radius;
            }
        }
        return true;
    }
    
    // TC: O(nlogn + mlogm + nlogn)
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        if(houses.empty())
            return true;
        if(heaters.empty())
            return false;
        
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        
        int low = 0, high = abs(max(houses.back(), heaters.back()) - houses.front());
        
        while(low < high) {
            int radius = low + (high - low) / 2;
            // check if the radius is enough to cover all the houses
            if(housesCovered(houses, heaters, radius))
                high = radius;
            else
                low = radius + 1;
        }
        return high;
    }
};
