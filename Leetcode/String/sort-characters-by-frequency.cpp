/*
    https://leetcode.com/problems/sort-characters-by-frequency/
    
    TC: O(N), SC: O(1)
    Sorting 256 chars is constant + linear traversal
*/
class Solution {
public:
    string frequencySort(string s) {
        // (char, frequency)
        vector<pair<int, int>> char_freq(256);
        for(int i = 0; i < char_freq.size(); i++) {
            char_freq[i].first = i;
            char_freq[i].second = 0;
        }
        // for each char, store its frequency
        for(const char &c: s)
            char_freq[c].second += 1;
        
        // sort the chars based on their frequencies
        sort(char_freq.begin(), char_freq.end(), 
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.second > b.second;
             });
    
        string result;
        for(int i = 0; i < char_freq.size(); i++)
            // if current char is present in string
            if(char_freq[i].second) {
                char c = char_freq[i].first;
                // add the chars 
                while(char_freq[i].second--)
                    result += c;
            }

        return result;
    }
};
