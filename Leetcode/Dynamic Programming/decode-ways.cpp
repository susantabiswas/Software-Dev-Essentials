/*
    91. Decode Ways
    https://leetcode.com/problems/decode-ways/
*/

class Solution {
public:
    // check if the combined number is valid or not
    // since the combination only makes sense when it is not a 
    // single digit number, so range is from 10 to 26
    bool isValidNumber(string s) {
        int num = stoi(s);
        return num >= 10 && num <= 26;
    }
    
    int numDecodings(string s) {
        vector<long long> dp(s.size(), 0);
        
        // each single char can be decoded iff it is 1-9
        if(s[0] != '0')
            dp.front() = 1;
        
        // we start the traversal, for each char:
        // we can have it as a single char iff 1-9 and add ways of decoding with i-1 chars
        // we can combine it with previous char iff 10-26, add ways of decoding with i-2 chars
        // NOTE: for the first valid occurence of double digit combination i-2 <0, so we make it 1
        for(int i = 1; i < s.size(); i++) {
            int single_char = s[i] == '0' ? 0 : dp[i-1];
            int combine_char = isValidNumber(s.substr(i-1,2)) ? ((i-2) < 0 ? 1 : dp[i-2]) 
                                                                : 0;
            dp[i] = single_char + combine_char;
        }
        
        return dp.back();
    }
};
