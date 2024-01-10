/*
    https://leetcode.com/problems/paint-house/
    
    TC: O(n)
    SC: O(1)
    
    Idea is to track the min cost accumulated when the given house is painted with each of the colors.
    For the current house, if we want to color it, we should consider the cost when the last house was
    colored with some other color.
    
    So when current house is painted with red, we can only take min cost accumulated when the last
    house was painted with either blue or green
    
    This is similar to house robber problem
*/
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        
        if(n == 0)
            return 0;
        
        // min cost accumulated when the last house is painted with the below colors
        int red_prev = costs[0][0], green_prev = costs[0][2], blue_prev = costs[0][1];
        // min cost accumulated when the current house is painted with the below colors
        int red = 0, green = 0, blue = 0;
        
        for(int i = 1; i < n; i++) {
            red = costs[i][0] + min(blue_prev, green_prev);
            blue = costs[i][1] + min(red_prev, green_prev);
            green = costs[i][2] + min(red_prev, blue_prev);
            
            red_prev = red, blue_prev = blue, green_prev = green;
        }
        
        return min({red_prev, green_prev, blue_prev});
    }
};
