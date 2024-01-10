/*
    https://leetcode.com/problems/paint-house/
    
    SOLUTION 1
    TC: O(nk^2)
    SC: O(k)
    
    Similar to Paint House I, this is a generalized problem with k possible colors
    
    Idea is to track the min cost accumulated when the given house is painted with each of the colors.
    For the current house, if we want to color it, we should consider the cost when the last house was
    colored with some other color.
    
    Eg when current house is painted with red, we can only take min cost accumulated when the last
    house was painted with either blue or green
    
    This is similar to house robber problem
    
    SOLUTION 2: Optimization
    TC: O(nk)
    SC: O(1)
    
    Here the idea is that we don't have to track the cost incurred for all the colors till last house.
    We just need the 2 min cost colors till last house, we use one of them with the min cost color of current house.
    We track 2 min cost colors because for the next house the min cost color might be the same as one of the current
    two house colors.
*/
class Solution {
public:
    int sol1(vector<vector<int>>& costs) {
        if(costs.empty())
            return 0;
        
        int k = costs[0].size();
        int n = costs.size();
        
        vector<int> prev(k, 0), curr(k, INT_MAX);
        prev = costs[0];
        
        for(int i = 1; i < n; i++) {
            // for the current house, find out the cost when
            // we paint the current house with each of the colors
            for(int color = 0; color < k; color++) {
                // IMP: Initialize the current value otherwise it will use its previous value
                curr[color] = INT_MAX;
                
                // If we color the current house with 'color', then find the min cost color
                // that can be done on the previous house
                for(int prev_color = 0; prev_color < k; prev_color++) {
                    if(color != prev_color)
                        curr[color] = min(curr[color], prev[prev_color] + costs[i][color]);
                }
            }
            
            prev = curr;
        }
        return *min_element(prev.begin(), prev.end());
    }
    
    // TC: O(nk)
    // SC: O(1)
    int sol2(vector<vector<int>>& costs) {
        if(costs.empty())
            return 0;
        
        int k = costs[0].size();
        int n = costs.size();
        
        // <cost, color>
        // min and 2nd min cost accumulated till last house 
        pair<int, int> min1_prev = {INT_MAX, -1}, min2_prev = {INT_MAX, -1};
        // min and 2nd min cost accumulated for current house 
        pair<int, int> min1_curr = {INT_MAX, -1}, min2_curr = {INT_MAX, -1};
        
        // find the min1 and min2 color costs for the 1st house
        for(int i = 0; i < k; i++) {
            if(costs[0][i] < min1_prev.first) {
                min2_prev = min1_prev;
                min1_prev = {costs[0][i], i};
            }
            else if(costs[0][i] < min2_prev.first)
                min2_prev = {costs[0][i], i};
        }
        
        for(int i = 1; i < n; i++) {
            // init the current min and 2nd min painting costs for the
            // current house
            min1_curr = {INT_MAX, -1}, min2_curr = {INT_MAX, -1};
            
            // for the current house, find the 2 min cost
            // colors
            for(int color = 0; color < k; color++) {
                // total cost incurred when painted with 'color'
                pair<int, int> color_cost = {INT_MAX, -1};
                
                // min accumulated cost with the current color
                // since we know the 2 min costs colors till last house, the current
                // color can be used with one of them only
                if(color != min1_prev.second) 
                    color_cost = {costs[i][color] + min1_prev.first, color};
                else
                    color_cost =  {costs[i][color] + min2_prev.first, color};
                
                // Since we track the 2 min cost colors for current house, check
                // if the current color makes one
                if(color_cost.first < min1_curr.first) {
                    min2_curr = min1_curr;
                    min1_curr = color_cost;
                }
                else if(color_cost.first < min2_curr.first)
                    min2_curr = color_cost;
            }
            
            min1_prev = min1_curr;
            min2_prev = min2_curr;
        }
        return min1_prev.first;
    }
    
    int minCostII(vector<vector<int>>& costs) {
        // return sol1(costs);
        return sol2(costs);
    }
};
