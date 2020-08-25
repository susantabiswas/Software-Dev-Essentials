/*
    https://leetcode.com/problems/valid-palindrome/submissions/
    
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0, j = s.size();
        
        while(i < j) {
            // skip the non-alpha numeric chars
            while(i < j && !isalnum(s[i]))
                ++i;
            while(j > i && !isalnum(s[j]))
                --j;
            
            if(tolower(s[i]) != tolower(s[j]))
                return false;
            
            ++i, --j;
        }
        return true;
    }
};
