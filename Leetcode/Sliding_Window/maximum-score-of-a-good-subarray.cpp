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
