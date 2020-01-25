/*
    https://leetcode.com/problems/trapping-rain-water/
*/
class Solution {
public:
    // Using 2 pointers
    // TC: O(N), SC: O(1)
    int trap(vector<int>& height) {
        int total_water = 0, max_left = 0, max_right = 0;
        int left = 0, right = height.size() - 1;
        
        // The idea is to move in the direction of smaller height as that will
        // be the bounding height. Also when in the direction of smaller height, keep
        // track of the max height and all the elevations on the way smaller
        // than the max will be able to store water (max_dir_height - curr_height) and
        // the other bound is already ensured to be bigger than the current direction bound
        while(left < right) {
            // move towards left
            if(height[left] > height[right]) {
                max_right = max(max_right, height[right]);
                total_water += max_right - height[right];
                --right;
            }
            // move towards right
            else {
                max_left = max(max_left, height[left]);
                total_water += max_left - height[left];
                ++left;
            }
        }
        return total_water;
    }
    
    // Using stack
    // TC: O(N), SC: O(N)
    int trap2(vector<int>& height) {
        int total_water = 0;
        stack<int> h;
        
        for(int i = 0; i < height.size(); i++) {
            // if the current height is a blocking height for
            // the existing heights, then compute the water they can hold
            // with the left and right blocking heights
            while(!h.empty() && height[h.top()] < height[i]) {
                int inbetween_height = h.top();
                h.pop();
                if(h.empty())
                    break;
                // no. of positions in between the bounding walls
                // this ensures that water blocks gets compensated for inbetween
                // blocks incase later on a much taller right bound is found
                int dist = i - h.top() - 1;
                total_water += dist * (min(height[i], height[h.top()]) - inbetween_height); 
            }
            h.emplace(i);
        }
        
        return total_water;
    }
    
    // Using extra O(N) array 
    // TC: O(N), SC:(N)
    int trap1(vector<int>& height) {
        if(height.empty())
            return 0;
        
        int total_water = 0, curr_water = 0;
        int max_height = height[0];
        // water[i]: water that can stay at ith position with boundaries on left and right
        vector<int> water(height.size(), 0);
        
        // considering the left boundary find the water capacity
        for(int i = 0; i < height.size(); i++) {
            if(height[i] > max_height) {
                max_height = height[i];
            }
            water[i] = max_height - height[i];
        }
        // considering the right boundary calculate the water capacity
        max_height = height.back();
        for(int i = height.size() - 1; i >= 0; i--) {
            if(height[i] > max_height)
                max_height = height[i];
            // water that can be placed is limited by the height of min(left, right) wall
            water[i] = min(water[i], max_height - height[i]);
            total_water += water[i];
        }
        return total_water;
    }
};
