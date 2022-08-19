/*
    https://leetcode.com/problems/maximal-rectangle/
*/
class Solution {
public:
    // finds the largest rectangle in histogram
    int largestHistogramRectangle(vector<int>& heights) {
        stack<int> s;
        int max_area = 0, curr_area = 0;
        const int N = heights.size();

        for(int i = 0; i < N; i++) {
            // if current height is a limiting height
            while(!s.empty() && heights[i] <= heights[s.top()]) {
                int curr = s.top();
                // pop the current height
                s.pop();
                curr_area = heights[curr] * (i - (s.empty() ? 0 : s.top() + 1));
                max_area = max(max_area, curr_area);
            }
            s.emplace(i);
        }
        // pop the remaining heights
        while(!s.empty()) {
            int curr = s.top();
            // pop the current height
            s.pop();
            curr_area = heights[curr] * (N - (s.empty() ? 0 : s.top() + 1));
            max_area = max(max_area, curr_area);
        }
        return max_area;
    }
    
    // Driver 
    int maximalRectangle(vector<vector<char>>& grid) {
        if(grid.empty())
            return 0;
        int max_area = 0;
        const int M = grid.size(), N = grid[0].size();
        // if grid is empty
        if(M == 0)
            return 0;
        vector<int> heights(N, 0);

        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++)
                // if current cell has 0, column height becomes 0
                heights[j] = grid[i][j] == '0' ? 0 : heights[j] + 1;
            max_area = max(max_area, largestHistogramRectangle(heights));
        }
        return max_area;
    }
};
