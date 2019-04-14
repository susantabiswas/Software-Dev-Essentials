/*
    424. Longest Repeating Character Replacement:
    Find the longest window which can have same characters when we can do K conversions.
    https://leetcode.com/problems/longest-repeating-character-replacement/
    
    In a window of characters, if we want to convert all the characters to the same type, then we convert every character to the most frequent character in that window. So we start with a window, use a vector to keep track of frequencies of characters in current window, this helps us to know the most frequent character in current window. Then we move the right position of window we check if the no. of switches required in current window is <= K or not. If yes then continue expanding else we start shrinking from left.
*/

class Solution {
public:
    int characterReplacement(string s, int k) {
        if(s.empty())
            return 0;
        
        // for keeping track of freq of chars
        vector<int> dict(128, 0);
        int flips = k;
        int max_len = 0;
        int max_freq = 0;
        
        int i = 0, j = 0;
        while(i < s.size()) {
            // increment frequency of current char and check if it
            // is has the most frequency or not
            ++dict[s[i]];
            max_freq = max(max_freq, dict[s[i]]);
            ++i;
            
            // calculate the no. of chars which needs to be changed
            // to the most frequent char
            int flips_req = i - j - max_freq;
            
            // if no. of changes that can be made is not enough
            // to convert every diff char in current window, then we start shrinking
            // the current window from left
            while(flips_req > k) {
                --dict[s[j]];
                ++j;
                // update changes required
                flips_req = i - j - max_freq;
            }
            // update max length if applicable
            max_len = max(max_len, i - j);
        }
        
        return max_len;
    }
};
