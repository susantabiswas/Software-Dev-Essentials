/*
    https://leetcode.com/problems/majority-element/
    
    SInce it is given that majority always exists, that means the majority will atleast be 1+N/2. So assume the first element to be majority and keep track of frequency of majority element. If an element is diff than majority element then decrease its freq untill it is 0, update the majority element as the current element.
*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int majority = 0, freq = 1;
        
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] != nums[majority])
                --freq;
            else
                ++freq;
            if(freq == 0)
                majority = i, freq = 1;
        }
            
        return nums[majority];
    }
};
