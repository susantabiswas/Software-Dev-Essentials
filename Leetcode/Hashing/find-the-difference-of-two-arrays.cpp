/*
    https://leetcode.com/problems/find-the-difference-of-two-arrays/
    
    TC: O(m + n)
    SC: O(m + n)
*/
class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> seen1, seen2;
        
        for(auto num: nums1)
            seen1.insert(num);
        
        for(auto num: nums2)
            seen2.insert(num);
        
        vector<vector<int>> result = {{}, {}};
        
        // numbers present in nums1 and not in nums2
        for(auto num: seen1)
            if(seen2.count(num) == 0)
                result[0].push_back(num);
        
        // nums present in nums 2 and not in nums1
        for(auto num: seen2)
            if(seen1.count(num) == 0)
                result[1].push_back(num);
        
        return result;
    }
};
