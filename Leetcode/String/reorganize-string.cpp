/*
    https://leetcode.com/problems/reorganize-string/submissions/
    
    TC:  O(N) + O(26log26)
*/
class Solution {
public:
    struct Comp {
        // min comp for max heap
        const bool operator()(const pair<char, int>& a, const pair<char, int>& b) const {
            return a.second < b.second;
        }    
    };
    
    string reorganizeString(string s) {
        vector<int> freq(26, 0);
        priority_queue<pair<char, int>, vector<pair<char,int>>, Comp> most_frequent;
        // find the frequency map of chars
        for(const char &c: s)
            freq[c - 'a'] += 1;
        
        for(int i = 0; i < 26; i++)
            if(freq[i] > 0)
                most_frequent.emplace(make_pair('a' + i, freq[i]));
        // if the max freq is more than n/2, then we wont be able 
        // separate same chars
        if(most_frequent.top().second > ceil((float)s.size() / 2))
            return "";
        // Initialize the string with blank pos indicated by '*'
        string result(s.size(), '*');
        
        // Put the max freq char in all even positions
        pair<char, int> curr = most_frequent.top();
        int i = 0;
        most_frequent.pop();
        for(i = 0; i < s.size() && curr.second--; i += 2)
            result[i] = curr.first;
        // Now all the odd positions are vacant and some of 
        // the later even positions
        // For any char with duplicates, we try to put them at positions
        // separated by 1 pos.
        while(!most_frequent.empty()) {
            curr = most_frequent.top();
            most_frequent.pop();
            
            while(curr.second--) {
                // Once we are finished with filling the even
                // positions, our index will be >= N, we start with odd pos. after that
                if(i >= s.size())
                    i = 1;
                result[i] = curr.first;
                i += 2;
            }
        }
        return result;
    }
};
