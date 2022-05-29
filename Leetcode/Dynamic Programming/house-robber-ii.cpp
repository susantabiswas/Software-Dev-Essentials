/*
    https://leetcode.com/problems/house-robber-ii/
    
    This is very similar to house robber problem, only caveat is the cycle.
    This cycle prevents us from robbing tyhe 1st and lats house at the same time.
    Since we can either rob 1st or last in a single run, we consider both the scenarios.
    1. We have houses from 1...N-1 (exclude last)
    2. We houses from 2...N (exclude first)
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    int robHouse(int start, int end, vector<int>&nums) {
        if(nums.empty())
            return 0;
        
        // Init with the values of the 1st house
        int rob_house = nums[start], rob_house_prev = nums[start];
        int skip_house = 0, skip_house_prev = 0;
        
        // Start the simulation from 2nd house
        for(int i = start+1; i <= end; i++) {
            rob_house = nums[i] + skip_house_prev;
            skip_house = max(rob_house_prev, skip_house_prev);
            
            rob_house_prev = rob_house, skip_house_prev = skip_house;
        }
        return max(rob_house_prev, skip_house_prev);
    }
    
    int rob(vector<int>& nums) {
        if(nums.size() <= 1)
            return nums.empty() ? 0 : nums[0];
        
        // Break the cycle by considering both the case:
        // House[1:N-1] => consider robbing 1st house and not last
        // House[2:N] => consider robbing last house and not 1st
        return max(robHouse(0, nums.size()-2, nums),
                robHouse(1, nums.size()-1, nums));
    }
};
