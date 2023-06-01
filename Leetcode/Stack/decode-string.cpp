/*
    https://leetcode.com/problems/decode-string/
    
    TC: O(N)
    SC: O(N)
    
    Idea is simply to use 2 stacks to preserve the nested patterns.
    1. One stack is used to save the frequencies for pattern that follows after it.
    2. One stack is used to save the string pattern.
    
    Start scanning from left to right. Whenever there is a number, save it in the stack for freq.
    If there is an opening [, save it in the data stack to mark a start of [] pair.
    If there is a string, capture the entire pattern and save it in the data stack.
    If there is ], then process all the data since the matching opening [ till that closing ].
    Save the result in the data stack agai, as this [] might be nested section.
    
    Handle the case of nested [], explained in line with code.
*/
class Solution {
public:
    string decodeString(string s) {
        string ans;
        // Stores the freq k for each pattern from L->R
        stack<int> freq;
        // stores the pattern from L->R
        stack<string> data;
        
        for(int i = 0; i < s.size(); ) {
            
            // extract the number k and save it
            if(isdigit(s[i])) {
                int num = 0;
                
                while(i < s.size() && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    ++i;
                }
                freq.push(num);
            }
            else if(s[i] == '[') {
                data.push("[");
                ++i;
            }
            // process the current freq * pattern
            else if(s[i] == ']') {
                int k = freq.top();
                freq.pop();
                
                string patt;
                vector<string> patts;
                // For the current [] pair, there can be multiple patterns
                // inside it, need to combine them all together to form a single
                // string and then apply the frequency multiplier.
                // eg: 3[2[a]3[c]] => 3[aaccc] 
                while(!data.empty() && data.top() != "[") {
                    patts.emplace_back(data.top());
                    data.pop();
                }
                reverse(patts.begin(), patts.end());
                for(auto str: patts)
                    patt += str;
                
                // pop opening [
                data.pop();
                
                string result;
                while(k--) {
                    result += patt;
                }
                
                data.push(result);
                ++i;
            }
            // extract the pattern
            else {
                string patt;
                while(i < s.size() && isalpha(s[i])) 
                    patt.push_back(s[i++]);
                
                data.push(patt);
            }
        }
        
        // At the end, we might have multiple linear strings
        // as a result of multiplication operation. Combine as single string
        // eg: 3[2[a]3[c]] => 3[aaccc] 
        vector<string> ans_list;
        while(!data.empty())
            ans_list.push_back(data.top()), data.pop();
        
        reverse(ans_list.begin(), ans_list.end());
        
        for(auto str: ans_list)
            ans += str;
        return ans;
    }
};
