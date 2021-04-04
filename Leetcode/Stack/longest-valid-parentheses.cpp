/*
    https://leetcode.com/problems/longest-valid-parentheses/
    
    The tricky part about this problem is to know the position where the 
    contiguous subarray breaks, e.g: ()((), here the 3rd brace is the breaking
    point between the first () and last ().
    
    To solve this problem, we use the normal approach to check for a valid parenthesis,
    a stack is used which saves the index position of each left brace. When we get a right brace, we
    pop the balancing opening brace and mark both these positions as True in valid_brace vector.
    
    Finally we iterate through the valid brace vector and look for the longest substring with True.
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> opening_brace;
        vector<bool> valid_brace(s.size(), false);
        int max_len = 0, curr_len = 0;
        
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '(')
                opening_brace.emplace(i);
            // if it is closing brace, balance it with an opening brace if avail
            else if(!opening_brace.empty()) {
                    int opening_idx = opening_brace.top();
                    // mark the opening and closing brace as valid
                    opening_brace.pop();
                    valid_brace[opening_idx] = valid_brace[i] = true;
                }
        }
        
        // find the longest window of valid balanced braces
        for(int curr = 0; curr < s.size(); ) {
            int i = curr;
            // cover the valid region
            while(i < s.size() && valid_brace[i])
                ++i;
            max_len = max(max_len, i - curr);
            curr = i + 1;
        }
        return max_len;
    }
};
