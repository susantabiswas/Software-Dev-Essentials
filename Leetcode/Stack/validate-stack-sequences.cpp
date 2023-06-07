/*
    https://leetcode.com/problems/validate-stack-sequences/
    
    TC: O(N)
    SC: O(N)
    
    Idea is to simply simulate the push/pop operations in the pushed array 
    and check if it is actually possible to get the element sequence of popped elements.
    
    We use a stack for simulation, if the current stack top doesnt match the current popped 
    element, then try pushing more elements till we get a matching element or we run out of elements.
    
    The reason we push and not pop at this point is, we don't have a matching element and all the elements
    so far were matched, so if we do a pop opeartion then the current element won't have any matching
    element in the popped array.
    
    Once we get a matching pushed element the same as the popped one, we remove that from the stack and
    move the popped array iterator forward for checking the next element.
*/
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> s;
        int n = pushed.size();
        
        int pop_idx = 0, push_idx = 0;
        
        for(; pop_idx < n; pop_idx++) {
            // Current popped element to check if it is possible
            int pop = popped[pop_idx];
            
            // keep pushing elements into the stack till the stack top
            // is not the same as the popped element
            // or if stack is empty
            while(push_idx < n && 
                  ((!s.empty() && s.top() != pop) || s.empty()) ) 
                s.push(pushed[push_idx++]);
           
            // If the stack top doesnt match the popped element, that means
            // it is not possible to get the popped element in the current position
            if(!s.empty() && s.top() != pop)
                return false;
            
            // Since we were able to get the popped element, pop the element from stack
            s.pop();
        }
        
        return pop_idx == n;
    }
};
