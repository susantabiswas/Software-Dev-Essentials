/*
    https://leetcode.com/problems/container-with-most-water/
    
    The idea is to start with first and last ends. Then each time move in the direction of
    smaller height, as the width will only be decreased everytime we move, so it is better to
    try to get a longer height.
*/
class Solution {
public:
    // TC: O(N), SC: O(1)
    int maxArea(vector<int>& height) {
        int max_area = 0, curr_area = 0;
        
        int start = 0, end = height.size() - 1;
        while(start < end) {
            curr_area = (end - start) * min(height[start], height[end]);
            max_area = max(max_area, curr_area);
            
            // move in the direction of smaller height  in hope of getting 
            // a longer height next time compensating for width reduction
            if(height[start] < height[end])
                ++start;
            else if(height[start] > height[end])
                --end;
            // when heights, are similar if we move only one
            // then the new area will be bounded by the curr height
            // and the width will obviously decrease making the area smaller.
            // So we can safely decrease both
            else 
                ++start, --end;
        }
        return max_area;
    }
};
