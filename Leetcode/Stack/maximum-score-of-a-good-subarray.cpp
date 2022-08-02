/*
    https://leetcode.com/problems/maximum-score-of-a-good-subarray/
    
    TC: O(n)
    SC: O(n)
    
    Looking at the score function, it is evident that is the formula for area of rectangle.
    So the question can be converted to - Max rectangle area such that k lies in that rectangle
    
    We use the same solution of largest histogram area and add additional check for checking 
    whether k falls in the rectangle area or not
*/
class Solution {
public:
    int largestHistogram(vector<int>& heights, int k) {
        stack<int> s;
        int max_area = 0, n = heights.size();
        
        for(int i = 0; i < n; i++) {
            while(!s.empty() && heights[i] < heights[s.top()]) {
                int curr = s.top();
                s.pop();
                
                // This is the number before the lower bound
                int lower_prev = s.empty() ? 0 : s.top();
                // Width of rectangle formed
                int width = i - (s.empty() ? 0 : s.top() + 1);
                int area = heights[curr] * width;
                // Current interval for k is [lower_prev+1, i-1], check if the
                // interval is valid
                if(lower_prev < k && k < i)
                    max_area = max(max_area, area);
            }
            s.emplace(i);
        }
        // process the remaining elements
        while(!s.empty()) {
            int curr = s.top();
            s.pop();
            
            int lower_prev = s.empty() ? 0 : s.top();
            int width = n - (s.empty() ? 0 : s.top() + 1);
            int area = heights[curr] * width;
            // Since upper bound is n for all remaining elements and k < n, we don't check for upper limit
            if(lower_prev < k)
                max_area = max(max_area, area);
        }
        
        return max_area;
    }
    
    int maximumScore(vector<int>& nums, int k) {
        return largestHistogram(nums, k);
    }
};
////////////////////////////


/*
    https://leetcode.com/problems/maximum-score-of-a-good-subarray/submissions/
    
    Using sliding window we can cover the valid windows and find the max score.
    Since i <= k <= j, so the subarray will always have index k, so we can expand 
    starting from index k in both directions, each time going in the direction of
    greater element.
    
    TC: O(N)
    SC: O(1)
*/

class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        // starting point of window
        int i = k, j = k;
        // starting point: index k
        int max_score = nums[k], min_num = nums[k], curr_min = nums[k];
        
        while(i > 0 || j < (int)nums.size() - 1) {
            // decide whether to expand on left or right
            if(i == 0)
                ++j;
            else if(j == nums.size()-1)
                --i;
            // both the indices can expand safely 
            else if(nums[i-1] > nums[j+1])
                --i;
            else
                ++j;
            curr_min = min(nums[i], nums[j]);
            min_num = min(min_num, curr_min);
            max_score = max(max_score, min_num * (j - i + 1));
            
        }
        return max_score;
    }
};
