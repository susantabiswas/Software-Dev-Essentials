/*

    https://leetcode.com/problems/jump-game-ii/
    
    TC: O(n)
    SC: O(1)
    
    Idea is to keep track of the max reach possible from the positions we have seen so far 
    and also the current jump we are following to move.
    
    If we have reached the end of current jump length, then we take a jump and go till the currently known
    max reach point.

*/
class Solution {
public:
    int jump(vector<int>& nums) {
        int max_reach = 0, curr_reach = 0;
        int jumps = 0;
        
        for(int i = 0; i < nums.size(); i++) {
            max_reach = max(max_reach, i + nums[i]);
            
            // end can be reached using the current jump
            if(curr_reach >= nums.size() - 1)
                break;
            
            // current jump distance is covered, now out of all the previously
            // seen jump positions, we take jump from the one that takes us the farthest
            if(curr_reach == i) {
                ++jumps;
                curr_reach = max_reach;
            }
        }
        return jumps;
    }
};
