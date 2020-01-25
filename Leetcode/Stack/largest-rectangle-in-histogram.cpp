/*
    https://leetcode.com/problems/largest-rectangle-in-histogram/
*/
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        const int N = heights.size();
        int max_area = 0, curr_area = 0;
        stack<int> s;
        
        // For each block we find the area while considering 
        // that block to be part of the area and be the limiting building
        for(int i = 0; i < N; i++) {
            // right side smaller limiting building found
            while(!s.empty() && heights[s.top()] > heights[i]) {
                int curr_idx = s.top();
                s.pop();
                curr_area = heights[curr_idx] * (i - (s.empty() ? 0 : s.top() + 1));
                max_area = max(max_area, curr_area);
            }
            s.emplace(i);
        }
        
        // find the area for the remaining buildings
        while(!s.empty()) {
            int curr_idx = s.top();
            s.pop();
            curr_area = heights[curr_idx] * (N - (s.empty() ? 0 : s.top() + 1));
            max_area = max(max_area, curr_area);
        }
        return max_area;
    }
};
