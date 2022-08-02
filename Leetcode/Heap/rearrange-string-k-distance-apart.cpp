/*
    https://leetcode.com/problems/rearrange-string-k-distance-apart/
    
    TC: O(n + nlogm), n = no. of chars, m = no. of unique chars
    SC: O(m + k)
    
    Since we need to ensure that each same char is atleast k distance away, this means
    we just need to check if it is possible to place unique numbers in a k sized window until
    the chars are all covered. Now the chars with higher frequency should be put first otherwise 
    it will be very hard to put them atleast k distance apart later on.
    So in a window, put the elements by their frequency. If it is possible to rearrange the string
    to  get the answer, then we will be able to fill the window with diff chars.
    
    We use a heap to give the max freq element for the current window. Once the window is finished,
    scan again to pick the chars which still have freq count left for another window and repeat the process.
*/
class Solution {
public:
    string rearrangeString(string s, int k) {
        if(k == 0)
            return s;
        // Find the frequency of each char. 
        // The chars with higher frequency are put first 
        unordered_map<char, int> freq;
        for(auto ch: s)
            ++freq[ch];
        
        // Helps to find the max frequency char
        // <frequency count, char>
        priority_queue<pair<int, char>, vector<pair<int, char>>, less<>> max_heap;
        
        for(auto [ch, char_count]: freq)
            max_heap.emplace(make_pair(char_count, ch));
        
        // Stores the rearranged string
        string ans(s);
        // Since each char should be k distance away, that means there should be enough
        // unique chars to fill a k sized window
        vector<pair<int, char> > window(k);
        int write = 0;
        
        while(!max_heap.empty()) {
            int i = 0;
            // Put the chars in the current window
            for(i = 0; i < k && !max_heap.empty(); i++) {
                auto char_freq = max_heap.top();
                max_heap.pop();
                
                window[i] = char_freq;
                ans[write++] = char_freq.second;
            }
            // If the entire window was not filled with unique chars even though there are elements left,
            // then can't rearrange
            if(i < k && write < s.size())
                return "";
            // Current window was possible, take the elements for the next window
            for(int i = 0; i < k; i++)
                if(window[i].first > 1) {
                    --window[i].first;
                    max_heap.emplace(window[i]);
                }
        }
        
        return ans;
    }
};
