/*
    https://leetcode.com/problems/maximum-number-of-balloons/submissions/
    
    TC: O(N)
    SC: O(5) ~ O(1)
*/
class Solution {
public:
    int maxNumberOfBalloons(string text) {
        unordered_map<char, int> freq;
        // Find the frequency of each unique char
        for(char &ch: text)
            ++freq[ch];
        
        // Now the number of words that can be formed is limited by
        // the smallest frequency of required chars
        // 'l' and 'o' appear twice, so effectively for each word 2 chars are needed
        return min({freq['b'], freq['a'], freq['ll'] / 2,
                    freq['o'] / 2, freq['n'],});
    }
};
