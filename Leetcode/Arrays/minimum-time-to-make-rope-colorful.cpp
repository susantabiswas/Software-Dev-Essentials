/*
    https://leetcode.com/problems/minimum-time-to-make-rope-colorful/
    
    TC: O(N)
    SC: O(1)
    
    Since we want to avoid having balloons with same colors together, means
    we can't have a consecutive window of same color. 
    For a consecutive window of same color, we want to keep the burst the balloons 
    such that the duration is also kept min, so if there are m balloons with same color,
    we need to burst m-1 balloons and just leave one. 
    The one that should be left should have the longest duration, this ensures that duration
    is kept at min.
*/
class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int min_time = 0;
        
        for(int i = 0; i < colors.size(); ++i) {
            // Amongst the same colors, tracks the longest duration one
            int max_duration_color = neededTime[i];
            // Total duration of same color balloons
            int total_same_color_duration = neededTime[i];
            
            // check if there are consecutive balloons of same color,
            // we need to burst all the balloons and can keep only one.
            // We should try bursting the balloons with shorter duration,
            // implies the longest duration wont be bursted.
            while(i + 1 < colors.size() && colors[i+1] == colors[i]) {
                max_duration_color = max(max_duration_color, neededTime[i+1]);
                total_same_color_duration += neededTime[i+1];
                ++i;
            }
            // Check if there were atleast > 1 balloon with same color
            if(total_same_color_duration > neededTime[i])
                min_time += total_same_color_duration - max_duration_color;
        }
        return min_time;
    }
};
