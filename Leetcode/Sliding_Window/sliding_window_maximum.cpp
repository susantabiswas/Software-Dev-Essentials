/*
    239. Sliding Window Maximum
    https://leetcode.com/problems/sliding-window-maximum/
    
    Max element in k sized window sliding window
*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(nums.empty())
            return vector<int>{};
        
        deque<int> dq;
        vector<int> res;
        
        // push elements of first window
        int i = 0; 
        while(i < k) {
            if(dq.empty())
                dq.emplace_back(i);
            else if(nums[i] >= nums[dq.back()]){
                // add the element to deque such that all elements before it 
                // are greater than it, there is no point in having smaller elements before 
                // it which exists before it in array
                auto it = dq.rbegin();
                while(it != dq.rend() && nums[i] >= nums[*it]) {
                    dq.pop_back();
                    ++it;
                }
                dq.emplace_back(i);
            }
            else if(nums[i] < nums[dq.back()])
                dq.emplace_back(i);
            ++i;
        }
        
        // cover all the windows of size K
        while(i < nums.size()) {
            // get current max
            int curr_max = dq.front();
            res.emplace_back(nums[curr_max]);
            
            // remove first element of current window if it is in deque
            if(i-k == dq.front())
                dq.pop_front();
            
            // add new element of next window if applicable
            if(!dq.empty() && nums[i] >= nums[dq.back()]) {
                auto it = dq.rbegin();
                while(it != dq.rend() && nums[i] >= nums[*it]) {
                    dq.pop_back();
                    ++it;
                }
            }
            dq.emplace_back(i);
            // move to next window
            ++i;
            
        }
        
        res.emplace_back(nums[dq.front()]);
        return res;
    }
};
