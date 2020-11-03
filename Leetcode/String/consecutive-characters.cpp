/*
    https://leetcode.com/problems/consecutive-characters/
    
    Idea is to traverse the array and look at the 
    previous char each time to decide if are still part 
    of the window with only 1 unique char.
    TC: O(N)
*/
class Solution {
public:
    int maxPower(string s) {
        int curr_len = s.empty() ? 0 : 1; 
        int max_len = curr_len;
        
        for(int i = 1; i < s.size(); i++) {
            // same char as before means we can continue with same window
            if(s[i] == s[i-1]) {
                ++curr_len;
                max_len = max(max_len, curr_len);    
            }
            // reset window
            else
                curr_len = 1;
        }
        return max_len;
    }
};
