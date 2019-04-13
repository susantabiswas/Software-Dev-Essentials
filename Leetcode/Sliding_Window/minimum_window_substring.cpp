/*
    76. Minimum Window Substring
    
    Min window of S that contains alll chars of T
    https://leetcode.com/problems/minimum-window-substring/submissions/
    
    
    Solution:
        We take two indices i and j, end and start respectively of window. Then we calculate the
        number of chars of each type of T and total chars that needs to be covered. We expand the window
        till all the chars are not covered, each time decreasing count of total_chars when a req char is 
        encountered. Once char count for a char is <=0 we dont lower total_chars for that, since that
        means we have extra number of that char in current window. Once we cover everything, we try shrinking
        window size.
*/
class Solution {
public:
    string minWindow(string s, string t) {
        if(t.empty())
            return "";
        
        // take character count of string t
        unordered_map<char, int> char_count;
        // total chars in T
        int total_chars = 0;
        for(const char& c: t) {
            if(char_count.find(c) == char_count.end()) {
                char_count[c] = 1;
            }
            else {
                char_count[c] += 1;
            }
           total_chars += 1;
        }
        
        int i = 0, j = 0;
        int min_len = numeric_limits<int> :: max();
        int start = -1, end = -1;
        while(i < s.size()) {
            // if there are still chars from T to cover
            if(total_chars > 0) {
                // if current char is part of T
                if(char_count.find(s[i]) != char_count.end()) {
                    if(char_count[s[i]] > 0) {
                        --char_count[s[i]];
                        --total_chars;
                    }
                    else {
                        --char_count[s[i]];
                    }
                }
                // if all the chars have been covered, dont expand the window
                if(total_chars == 0)
                    continue;
                // expand the window
                ++i;
            }
            else {  
                // while all the chars are coevered try shrinking
                while(total_chars == 0)
                {
                    // check if current window is min
                    int curr_len = i - j + 1;
                    if(curr_len < min_len) {
                        min_len = min(min_len, i - j + 1);
                        start = j;
                        end = i;
                    }

                    // we try to shrink the window size since all T chars have been covered
                    // if current char is part of T
                    if(char_count.find(s[j]) != char_count.end()) {
                        // if count for current char is exactly the number of times required
                        // then total chars that needs to be covered needs an update
                        if(char_count[s[j]] >= 0) {
                         ++char_count[s[j]];
                            ++total_chars;
                        }
                        else 
                            // when there are still more number of current chars than required
                            ++char_count[s[j]];
                    }
                    // shrink the window
                    ++j;
                }
                // now since the window again doesnt contain all the chars, expand the window
                ++i;
            }
        }
        
        int curr_len = i - j + 1;
        if(curr_len < min_len && total_chars == 0) {
            min_len = min(min_len, i - j + 1);
            start = j;
            end = i;
        }
        if(start == -1)
            return "";
        return s.substr(start, end - start + 1);
    }
};
