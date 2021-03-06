/*
    https://leetcode.com/problems/make-two-arrays-equal-by-reversing-sub-arrays/
    
    Since reversal can be done any number of times, so in base case if we have 2 elements,
    we can reverse them. So we only need to ensure that both are having same element frequency, 
    since in worst case we can always reverse 2 elements to get what is required.
    
    TC: O(N), SC: O(N)
*/

class Solution {
public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        if(target.size() != arr.size())
            return false;
        // find the frequency map of target
        unordered_map<int, int> freq;
        for(const int& num : target)
            freq[num] += 1;
        
        // check if the second array has the same set of element frequencies
        for(const int& num: arr) {
            if(freq.count(num)) {
                --freq[num];
                if(freq[num] == 0)
                    freq.erase(num);
            }
            else
                return false;
        }
        
        return freq.empty();
    }
};
