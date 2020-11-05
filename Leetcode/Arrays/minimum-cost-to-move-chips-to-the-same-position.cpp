/*
    https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position/submissions/
    
    Idea is that for each even position, we can move all coins at other 
    even positions with cost = 0 by moving to intermediate even positions.
    For odd coins, we do the same and finally using cost=1 take +1 step.
    
    Similar argument can be made for odd positions, other odd position coins
    can be moved with cost = 0, since difference between each odd number is also 2.
    
    TC: O(N)
    SC: O(1)
*/

class Solution {
public:
    int minCostToMoveChips(vector<int>& position) {
        // count the total coins at even and odd positions
        int n_even = 0, n_odd = 0;
        for(auto &pos: position) {
            if(pos % 2 == 0)
                ++n_even;
            else
                ++n_odd;
        }
        
        int min_cost = INT_MAX;
        for(auto &pos: position) {
            // cost for current position
            int cost = 0;
            cost = pos % 2 ? n_even : n_odd;
            min_cost = min(min_cost, cost);
        }
        
        return min_cost;
    }
};
