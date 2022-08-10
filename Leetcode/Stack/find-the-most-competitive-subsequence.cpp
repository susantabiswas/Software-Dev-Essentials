/*
    https://leetcode.com/problems/find-the-most-competitive-subsequence/
    
    TC: O(N)
    SC: O(k)
*/
class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        // We use it as a stack
        vector<int> smallest_sub;
        
        for(int i = 0; i < nums.size(); i++) {
            // if current number is smaller than the elements 
            // in current subsequence, then we can make the sequence 
            // even smaller lexographically, by pushing it at its best position. The
            // thing to consider to ensure there are atleast elements remaining 
            // in array which can fill the k sized window
            while(!smallest_sub.empty() && nums[i] < smallest_sub.back()
                 && ((k - smallest_sub.size() + 1) <= nums.size() - i))
                smallest_sub.pop_back();
            
            if(smallest_sub.size() < k)
                smallest_sub.push_back(nums[i]);
        }
        
        return smallest_sub;
    }
};
