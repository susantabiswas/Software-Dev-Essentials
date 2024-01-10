/*
    https://leetcode.com/problems/paint-house-ii/
    
    TC: O(nk^2)
    SC: O(k)
    
    Similar to Paint House I, this is a generalized problem with k possible colors
    
    Idea is to track the min cost accumulated when the given house is painted with each of the colors.
    For the current house, if we want to color it, we should consider the cost when the last house was
    colored with some other color.
    
    Eg when current house is painted with red, we can only take min cost accumulated when the last
    house was painted with either blue or green
    
    This is similar to house robber problem
*/
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
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
};
