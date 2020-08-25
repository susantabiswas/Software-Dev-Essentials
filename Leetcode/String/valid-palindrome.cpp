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
            // Now current chars are sure to be alpha numeric
            // when one of them is alphabet and other is a number
            // cant be a palindrome
            if(i < j && (isalpha(s[i]) ^ isalpha(s[j]))) 
                return false;
            else if(i < j) {
                // if both are alphabets
                if(isalpha(s[i])) {
                    if(tolower(s[i]) != tolower(s[j]))
                        return false;
                }
                // if both are numbers
                else if(s[i] != s[j]) {
                    return false;}
            }
            ++i, --j;
        }
        return true;
    }
};
