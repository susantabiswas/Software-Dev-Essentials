/*
    https://leetcode.com/problems/intersection-of-two-arrays-ii/submissions/
    
    Idea is to create a hash table and store the frequency of all the
    elements of the smaller length array. Then iterate through the longer
    array and check in the hash table if the element exists. If it does, add to 
    the list of common elements.
    
    TC: O(max(M, N))
    SC: O(min(M, N))
*/
class Solution {
public:
    // Find the frequency of all the elements 
    void findFrequency(vector<int> *smaller, unordered_map<int, int>& freq) {
        for(int &num: *smaller)
            ++freq[num];
    }
    
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        // Hash table of element frequency
        unordered_map<int, int> freq;
        vector<int> common;
        
        // pick the smaller array and find the frequency map
        vector<int> *smaller = nullptr, *larger = nullptr;
        if(nums1.size() < nums2.size()) 
            smaller = &nums1, larger = &nums2;
        else 
            smaller = &nums2, larger = &nums1;
        
        
        findFrequency(smaller, freq);
        
        for(int &num: *larger) {
            // Common element found
            if(freq.count(num) && freq[num] > 0) {
                common.emplace_back(num);
                // remove the current instance
                --freq[num];
                if(freq[num] == 0)
                    freq.erase(num);
            }    
        }
            
        return common;
    }
};
