/*
    https://leetcode.com/problems/remove-k-digits/
    
    TC: O(N), SC: O(N)
    
    On removing even a single digit, the number becomes smaller.
    Since we know that the number will get smaller, then to decide which digit
    to remove when K=1, we look for the largest digit whose right digit(if exists)
    is smaller, so that if that is removed then the right digit takes its position
    and makes the already smaller number smaller. If instead we take out a digit on left 
    of that larger one, then the larger digit takes its position when the number becomes smaller,
    making it not the smallest.
    EG: 12343
    remove 4: 1233
    remove 3: 1243, 4 takes the position of 3
*/
class Solution {
public:
    string removeKdigits(string num, int k) {
        // Idea is to use a stack, the number is inserted
        // when it is bigger than the stack top
        string s;
        for(int i = 0; i < num.size(); i++) {
            while(!s.empty() && s.back() > num[i] && k) 
                s.pop_back(), --k;
            s += num[i];
        }
        // when digits are in non-decreasing order, remove k from last
        while(!s.empty() && k)
            s.pop_back(), --k;
        // remove leading zeros
        int i = 0;
        while(i < s.size() && s[i] == '0')
            ++i;           
        
        // if the string is empty after removing zeros, then return 0, else the remaining string
        return i == s.size() ? "0" : s.substr(i);
    }
};
