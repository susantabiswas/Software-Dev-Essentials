/*
    https://leetcode.com/problems/sliding-window-maximum/
    
    Sol1:
    Idea is to use a monotonic queue. The element at the front is always ensured the greatest.
    Any new element is pushed such that the smaller elements before it are popped, this is because current
    element will be more recent and hence makes no sense to keep a smaller and older element.
    If it is smaller it is added, because this smaller element might become the greatest for its window
    
    Sol2:
    Use a height balanced tree to keep track of greatest element in log(k) time and at a time it has all the elements for 
    that window
*/
class Solution {
public:
    // SOLUTION 1: Monotonic queue
    // TC: O(N)
    // SC: O(k)
    vector<int> queueSol(vector<int>& nums, int k) {
        // Front always has the greatest element
        deque<int> q;
        // add the 1st window elements
        int idx = 0;
        for(; idx < k; idx++) {
            // pop elements from back till a greater element comes
            // same elements are kept
            while(!q.empty() && nums[idx] > q.back())
                q.pop_back();
            q.emplace_back(nums[idx]);
        }
        
        vector<int> result;
        // give the max for the current window
        result.emplace_back(q.front());
            
        for(; idx < nums.size(); idx++) {
            // move the window
            // remove the 1st element of last window
            if(q.front() == nums[idx - k])
                q.pop_front();
            // add the new element of current window
            while(!q.empty() && q.back() < nums[idx])
                q.pop_back();
            q.emplace_back(nums[idx]);
            // give the max for the current window
            result.emplace_back(q.front());
            
        }
        return result;
    }
    
    // SOLUTION 2: Height balanced tree
    // TC: O(nlogm), n = total elements, m = unique elements
    // SC: O(k)
    // Each element will be pushed once and there are n elements
    vector<int> treeSol(vector<int>& nums, int k) {
        map<int, int> elements;
        vector<int> result;
        
        // process the 1st window
        int idx = 0;
        for(; idx < k; idx++) 
            ++elements[nums[idx]];
        
        // max from 1st window
        result.emplace_back(elements.rbegin()->first);
        
        // process the other windows
        for(; idx < nums.size(); idx++) {
            // move the window
            --elements[nums[idx - k]];
            if(elements[nums[idx - k]] == 0)
                elements.erase(nums[idx - k]);
            
            // add the new element of current window
            ++elements[nums[idx]];
            // max in current window
            result.emplace_back(elements.rbegin()->first);
        }
        return result;
    }
    
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // return queueSol(nums, k);
        return treeSol(nums, k);
    }
};
