/*
    424. Longest Repeating Character Replacement:
    Find the longest window which can have same characters when we can do K conversions.
    https://leetcode.com/problems/longest-repeating-character-replacement/
    
    In a window of characters, if we want to convert all the characters to the same type, then we convert every character to the most 
    frequent character in that window. So we start with a window, use a vector to keep track of 
    frequencies of characters in current window, this helps us to know the most frequent character 
    in current window. Then we move the right position of window we check if the no. of switches required 
    in current window is <= K or not. If yes then continue expanding else we start shrinking from left.

    Observation: 
        - The substring with the max no. of common chars is the and, as that substring needs the least no. of replacements.
        - max_freq: This is the max freq of a char seen in the overall string and not just the current window.
            We track it globally because, unless there is a char which has more concentration than current max_freq char, we will never 
            find the answer.
        - The reason we dont bother updating max_freq in the shrinking window is that it serves no purpose, we have already found the longest
            window that satisfies the constraint and the current char made the window invalid, so we just want to shrink the window enough
            so that the window is valid again.
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
            // We don't need to update the max_freq for a window
            // that is smaller than the max length window so far as it
            // doesn't help us anyway.
            // eg: aaabcccccc, k = 0
            // Here max_freq = 3 will stay till ccc is there in the current window.
            // Once we get aaab, our window is invalid and we will shrink the window
            // then next time again the window' start will shift right (even end is shifting 1 step right)
            // as the window is still not valid.
            // This goes even when bccc is the current window, then the next turn => window = cccc
            // Now this is a new max valid window and will automatically force the max_freq to be updated to 4
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
                // we don't update max_freq because any valid string 
                // length created here will still be smaller,  knowing this fact
                // it doesnt matter if the shrunken window is valid or not. We just want to
                // make the window valid again which became invalid because of most recent char,
                // so we just shrink by 1, which makes flips_req valid again and we try to expand
                // again to search for a better longer valid window, incase we still end up with an
                // invalid window, we will again be inside this loop and repeat the step
                flips_req = i - j - max_freq;
            }
            // update max length if applicable
            max_len = max(max_len, i - j);
        }
        
        return max_len;
    }
};
