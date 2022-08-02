/*
    https://leetcode.com/problems/intersection-of-two-arrays/
    
    We use a hash table to keep track of all the unique elements of smaller array 
    in constant time. Then traverse the bigger list to find the unique elements using the
    hash table.
*/

class Solution {
public:
    // TC: O(M + N), SC: O(min(M, N))
    // Using Hashing
    vector<int> hashingSol(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        // find the smaller array to create a hash table
        vector<int> *smaller = nums1.size() < nums2.size() ? &nums1 : &nums2;
        vector<int> *bigger = nums1.size() > nums2.size() ? &nums1 : &nums2;
        
        unordered_set<int> elements(smaller->begin(), smaller->end());
        
        // Now in the bigger array, check each element if it belongs to the other array
        // using the hash table
        for(const int& num: *bigger) 
            if(elements.count(num)) {
                result.emplace_back(num);
                // remove the current element from hash table
                elements.erase(num);
            }
        return result;
    }
    
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        return hashingSol(nums1, nums2);
    }
};
