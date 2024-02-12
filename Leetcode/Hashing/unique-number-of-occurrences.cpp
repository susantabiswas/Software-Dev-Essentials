/*
    https://leetcode.com/problems/unique-number-of-occurrences/
    
    TC: O(n)
    SC: O(m), m = no. of unique numbers
    
*/
class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        // track the unique frequencies
        unordered_set<int> uniq_freq;
        unordered_map<int, int> freq;
        
        for(auto num: arr) {
            ++freq[num];
        }
        
        // check if there are duplicates frequencies
        for(auto [_, count]: freq) {
            if(uniq_freq.count(count))
                return false;
            
            uniq_freq.insert(count);
        }
        return true;
    }
};
