/*
    https://leetcode.com/problems/bulb-switcher-iv/submissions/
    
    Things to note:
    1. Min flips are req
    2. Flip at ith pos, results in flip of all the bulbs on right.
    
    So it will be a waste to flip a switch on j, and bulb at i-th pos
    needs a flip where i < j. Since flipping the ith bulb might make the 
    jth bulb state diff from what is desired, so we start flipping from left side.
    
    Now for odd number of flips, the final state is diff than the orig state and for even
    flips the final state is the same as the orig state. 
    
    So we start traversal from left side, checking if the current bulb state matches the target 
    bulb position, if not flip and also track number of flips done.
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    int minFlips(string target) {
        int flips_done = 0;
        
        for(const char &c: target) {
            int pos_state = 0;
            // check the state of bulb of current position
            // after going through flips.
            // Odd number of flips does inversion of original state
            pos_state = (flips_done % 2) ? !pos_state : pos_state;
            if(pos_state != c - '0')
                ++flips_done;
        }
        return flips_done;
    }
};
