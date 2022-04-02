/*
    https://leetcode.com/problems/delete-and-earn/
    
    // TC: O(N), N = Max element
    // SC: O(M), M = No. of distinct elements
    
    Intuition
    Things to note/observe in the problem:
    1. Picking a number eliminates num+1 and num-1. So you need to be sure about
        the possible gain by picking a number. Need to account for upcoming instances of the
        number. Eg. [3, 4, 3, 4], If we pick 3, it leaves [3,3] => total: 6
                                If we pick 4, it leaves [4,4] => total: 8
    2. Since we need to account for the total reward associated with a number, we need to 
        compute that first.
    3. Once we know about the possible reward associated with each number and knowing the
        constraint that adjacent numbers in number line can't be picked. Eg, [1,2,3] then
        if 1 is picked, only 3 can be picked not 2
    4. Now this entire things looks very similar to 'House Robber' problem, where you can rob
        houses but not adjacent ones to accumulate max rewards. If we arrange the total points for each
        number on a number line associated with each number, then that looks similar to the houses in 
        house robber problem. Also the constraint of not picking num+1 and num+2 will be done automatically
        since you anyway can't pick adjacent houses. Eg : [1,2,3] => If 2 is picked, both 1 and 3 can't be picked
        
    Ref:
	House Robber problem
	https://leetcode.com/problems/house-robber/
*/
class Solution {
public:
    // TC: O(N), N = Max element
    // SC: O(M), M = No. of distinct elements
    int deleteAndEarn(vector<int>& nums) {
        // <num: total reward associated>
        unordered_map<int, int> points;
        // find the total pt that we can get for each number
        for(int num: nums)
            points[num] += num;
        
        // Idea is for each number check if we can get more score by 
        // 1. picking that number + max value without the previous number 
        // 2. Not using current number and using the max seen till last number either
        // by using last or skipping last
        int use_curr = 0, use_prev = 0;
        int skip_curr = 0, skip_prev = 0;
        
        int max_num = *max_element(nums.begin(), nums.end());
        // The hash map only has the numbers in the array, but we need to simulate
        // the number line otherwise the adjacent elements in hash table would be treated
        // as adjacent numbers. Eg [1,3,3,1] => points: <1:1>, <3:6>. Directly running the
        // loop would consider 1 and 3 as adjacent and only one would be picked
        for(int num = 1; num <= max_num; num++) {
            use_curr = skip_prev + points[num];
            skip_curr = max(skip_prev, use_prev);
            
            use_prev = use_curr, skip_prev = skip_curr;
        }
        return max(use_prev, skip_prev);
    }
};