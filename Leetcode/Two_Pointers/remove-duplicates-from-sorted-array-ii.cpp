/*
    https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
    
    TC: O(n)
    SC: O(1)
    
    Iterate throught the array:
        for current num, iterate till we have traversed all the duplicates of it.
        Then write the element and its duplicate (max 2)
*/
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int write = 0;
        int k = 2; // max duplicates allowed
        
        for(int i = 0; i < nums.size(); ) {
            int start = i;
            int freq = 0;
            
            // traverse till all the duplicates for the current num are covered
            while(i < nums.size() && nums[start] == nums[i])
                ++i, ++freq;
            
            // write the element(s)
            freq = min(freq, k);
            for(int i = 0; i < freq; i++)
                nums[write++] = nums[start];
        }
        
        return write;
    }
};
