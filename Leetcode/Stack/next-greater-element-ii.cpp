/*
    https://leetcode.com/problems/next-greater-element-ii/
    SOLUTION 1
    To find the nexxt greater element in a linear array, we can use a stack and traverse 
    from right to left ensuring that increasing order is maintained inside the stack.
    But since this is cyclic, we continue search after the Nth element to continue from 1st element.
    To handle this, we try to find the next greater in traditional scenario, and mark the positions
    where it couldnt be found. 
    Then we start traversal from left, maintain a queue of increasing order elements. For each position
    check if it is marked without a next greater element or not, if it doesnt have one, start looking
    for the first element from left greater elements queue.
    
    TC: O(N^2), 
        since in 2nd pass, we can go through all the previous elements in left
        and this can happen at most n/2.
        1 + 2 + ...  n/2 ~ n^2
    SC: O(N)
    
    
    SOLUTION 2
    
    Since the array is cyclic, we can perform the normal algorithm for finding closest greater element
    twice for each element. So we start from right side and continue till 0th index, it will capture the
    obvious greater element and all the elements also get captured in the order. Now we do the traversal
    again from right, but this time we will also have the info about the elements which we get if the array is
    traversed in cycllic manner.
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    // SOLUTION 1
    vector<int> sol1(vector<int> &nums) {
        const int N = nums.size();
        vector<int> next_greater(N, INT_MAX);
        // greatest element on left/right will be on top
        // in right to left pass, this is used as a stack
        // in left to right pass, this is used as a queue
        deque<int> greater_elements;
        
        // 1st pass: find if next greater element exists on the right 
        // side as if the array is linear
        for(int i = N-1; i >= 0; i--) {
            // find a greater element
            while(!greater_elements.empty() &&
                 greater_elements.back() <= nums[i])
                greater_elements.pop_back();
            // check if there is any element greater
            if(!greater_elements.empty())
                next_greater[i] = greater_elements.back();
            greater_elements.emplace_back(nums[i]);
        }
        
        // remove the right side elements
        while(!greater_elements.empty())
            greater_elements.pop_back();
        
        // 2nd pass
        for(int i = 0; i < N; i++) {
            // if no greater element was found on right,
            // check if there is one on left
            if(next_greater[i] == INT_MAX) {
                // look for the first leftmost element greater than current
                for(auto it = greater_elements.begin(); it != greater_elements.end(); it++)
                    if(*it > nums[i]) {
                        next_greater[i] = *it;
                        break;
                    }
            }
            // no next greater found
            if(next_greater[i] == INT_MAX)
                next_greater[i] = -1;
            if(greater_elements.empty() ||
               nums[i] > greater_elements.back())
                greater_elements.emplace_back(nums[i]);
        }
        return next_greater;
    }
    
    // SOLUTION 2
    vector<int> sol2(vector<int>& nums) {
        const int N = nums.size();
        vector<int> next_greater(N, -1);
        stack<int> greater_elements;
        
        // 1st pass: find if next greater element exists on the right 
        // side as if the array is linear
        for(int i = 2*N-1; i >= 0; i--) {
            // find a greater element
            while(!greater_elements.empty() &&
                 greater_elements.top() <= nums[i % N])
                greater_elements.pop();
            // check if there is any element greater
            if(next_greater[i % N] == -1 &&
               !greater_elements.empty())
                next_greater[i % N] = greater_elements.top();
            
            greater_elements.emplace(nums[i % N]);
        }
        
        return next_greater;
    }
    
    vector<int> nextGreaterElements(vector<int>& nums) {
        // return sol1(nums);
        return sol2(nums);
    }
};
