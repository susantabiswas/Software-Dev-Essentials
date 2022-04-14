/*
    https://leetcode.com/problems/132-pattern/
*/
class Solution {
public:
    // Sol 1: Value Optimization for Aj and Ak
    // TC: O(N)
    // SC: O(N)
    /*
        Goal: Find triplet such that Ai < Ak < Aj, where i < j < k.
        Intuition: 
        Whenever we are scanning from left to right or right to left, till pos 'idx',
        we want to ensure that Aj is max, Ak is max such that it is < Aj. This ensures that
        finding Ai becomes easier as both Aj and Ak are bigger values. But just tracking the
        highest value seen so far won't do, we need to keep track of local maximas of Aj and Ak,
        otherwise if we are just tracking the global maxima for Aj and Ak we might not find a 
        value where the triplet elements are not part of global maximas, minima etc.
            J
            /\
         j /  K
        /\/
        i k
        Look at the above eg, if we only tracked global J and K then we wouldnt have found (i, k, j) triplet.
        So it is important to keep track of nearest greatest elements. For keeping track of nearest greatest elements,
        we use stack.
        
        We scan from right to left and keep track of greatest (Aj) and second greatest (Ak) element,
        these are potential candidates. Since we are tracking the 2 greatest values, any Ai which is 
        smaller will form a 132 pattern with the tracked Aj and Ak values
    */
    bool sol1(vector<int>& nums) {
        // tracks 2nd highest element, candidate for Ak or "2"
        int nearest_second_highest = INT_MIN;
        // monotonically decreasing stack of values
        stack<int> nearest_greater;
        
        for(int i = nums.size() - 1; i >= 0; i--) {
            if(nums[i] < nearest_second_highest)
                return true;
            // If curr element is greater than last greatest, then there is no point keeping the 
            // previously seen smaller value, as we are scanning from right to left and a bigger 
            // value will only help find a smaller Ai
            // NOTE: not doing >= since then we need to handle the case where both nearest_second_highest
            // and curr greatest will have the same value
            while(!nearest_greater.empty() && nums[i] > nearest_greater.top()) {
                nearest_second_highest = nearest_greater.top();
                nearest_greater.pop();
            }
            nearest_greater.push(nums[i]);
        }
        return false;
    }
    
    // Sol 2: Tracking min on left and ensuring Aj and Ai are found always. Search for Ak
    // TC: O(N)
    // SC: O(N)
    /*
        Goal: Find triplet such that Ai < Ak < Aj, where i < j < k.
        Intuition: 
            We are trying to keep candidates for Ai and Aj while searching for Ak.
            We can use a stack to keep track of nearest greater element and a var to keep 
            track of smallest number seen so far. For each element we have [smallest_seen_so_far, curr_value],
            i.e pair(Ai, Aj), then we look for Ak such that Ak > smallest_seen_so_far of curr_value.
            
            The stack helps track the path from Aj to Ak, i.e decreasing value path.
                J
                /\
             j /  K
            /\/
            i k
    */
    struct Element {
        int val;
        int smallest_on_left;
        Element(int val, 
                int smallest_on_left) : val(val), smallest_on_left(smallest_on_left) {}
    };
    
    bool sol2(vector<int>& nums) {
        // monotonically decreasing stack of values, had it been increasing 
        // then the greater elements would be popped on seeing a smaller value.
        // This will result in loss of information for (Ai, Aj) pair, instead when we accept
        // smaller values we are retaining the local (Ai, Aj) pairs. If the next number is bigger
        // than current top, then keep popping till it has a bigger (Aj) one on left.
        stack<Element> nearest_greater;
        int smallest_on_left = INT_MAX;
        
        for(int k = 0; k < nums.size(); k++) {
            // If curr element is greater than last greatest, then there is no point keeping the 
            // previously seen smaller value, as we are scanning from left to right and a bigger 
            // value will only help find a smaller Ai
            while(!nearest_greater.empty() && nums[k] >= nearest_greater.top().val)
                nearest_greater.pop();
            // If the stack still has element, then the top is Aj candidate
            if(!nearest_greater.empty() && nums[k] > nearest_greater.top().smallest_on_left)
                return true;
            nearest_greater.push(Element(nums[k], smallest_on_left));
            smallest_on_left = min(smallest_on_left, nums[k]);
        }
        return false;
    }
    
    bool find132pattern(vector<int>& nums) {
        // return sol1(nums);
        return sol2(nums);
    }
};
