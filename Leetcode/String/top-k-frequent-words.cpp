/*
    https://leetcode.com/problems/top-k-frequent-words/submissions/
    
    TC: O(wlogw)
    SC: O(wL), w: no. of words, L: Length of longest word
*/
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> freq;
        // Calculate the freq of each word
        for(string &word: words)
            ++freq[word];
        
        vector<string> result;
        vector<pair<string, int>> freq_elements(freq.begin(), freq.end());
        // sort the array in decreasing order of word freq
        sort(freq_elements.begin(), freq_elements.end(), 
            [](pair<string, int> &a, pair<string, int> &b) -> bool {
                return a.second > b.second ||
                    (a.second == b.second && a.first < b.first);
            });
        
        for(int i = 0; i < k; i++) 
            result.emplace_back(freq_elements[i].first);
        
        return result;
    }
};
