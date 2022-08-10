/*
    https://leetcode.com/problems/longest-valid-parentheses/
    
    SOLUTION 1: Stack
    The tricky part about this problem is to know the position where the 
    contiguous subarray breaks, e.g: ()((), here the 3rd brace is the breaking
    point between the first () and last ().
    
    To solve this problem, we use the normal approach to check for a valid parenthesis,
    a stack is used which saves the index position of each left brace. When we get a right brace, we
    pop the balancing opening brace and mark both these positions as True in valid_brace vector.
    
    Finally we iterate through the valid brace vector and look for the longest substring with True.
    
    
    SOLUTION 2: DP
    Thing to note is ) marks the end of a valid chain of parenthesis.
    So we use a 1D array that saves the length of longest valid chain ending at ith position
    
    Then chars with ( are not processed as they by themselve can't tell whether valid or not, so dp[i] = 0
    
    When we get ), then two cases:
    1. Prev: ( => Complete pair formed so dp[i] = 2 + Previous chain (dp[i-2])
    2. Prev: ) => Dealing with a nested case, Go to the prev char of start of valid chain of last char, if that
    is (, then current can form a valid pair with it otherwise dp[i] = 0.
    If it forms a valid pair, then dp[i] = 2 + dp[i-1] + Previous chain (dp[i - dp[i-1] - 2])
*/
class Solution {
public:
    // SOLUTION 1: Stack
    // TC: O(N)
    // SC: O(N)
    int stackSol(string s) {
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
    
    // SOLUTION 2: DP
    // TC: O(N)
    // SC: O(1)
    int dpSol(string s) {
        if(s.empty())
            return 0;
        
        // dp[i] = Length of longest valid parenthesis chain ending at ith position
        vector<int> dp(s.size(), 0);    
        int max_len = 0;
        
        for(int i = 1; i < s.size(); i++) {
            // only closing brace can end a valid sequence
            // () found with the last char
            if(s[i] == ')' && s[i-1] == '(')
                dp[i] = 2 + (i >= 2 ? dp[i-2] : 0);
            // )) created with the last char, check if the char before the 
            // valid chain ending at i-1 is (
            // If that char is (, then ith char along with that char also constitutes the chain
            // ending at i-1 position
            // dp[i - dp[i-1] - 2] = Max length chain ending before the start of current chain
            else if(s[i] == ')' && s[i-1] == ')' && (i - dp[i-1] - 1) >= 0 && s[i - dp[i-1] - 1] == '(')
                dp[i] = 2 + dp[i-1] + ((i - dp[i-1] - 2) >= 0 ? dp[i - dp[i-1] - 2]: 0);
        
            max_len = max(max_len, dp[i]);
        }
        
        return max_len;
    }
    
    int longestValidParentheses(string s) {
        return stackSol(s);
        // return dpSol(s);
    }
};
