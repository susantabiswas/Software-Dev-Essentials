/*
    https://leetcode.com/problems/open-the-lock/
    
    TC: O(Deadends + W*W * (d^W)) ~ O(Deadends + 4*4 * (10 ^ 4)), 
    W = no. of wheels, Deadends = No. of deadends, d = no. of possible digits [0-9]
    
    We might end up exploring most of the numbers
    At each stage we iterate through all the wheels and for each wheel make a new string copy of size W.
    
    SC: O(d^W), Worst case when we end up adding almost all the combinations to visited set.
    
    This problem can be solved using BFS since we want to reach the target in min no. of steps
    and each step has no special property/weight.
    
    We track the levels of BFS and when the target is reached, return its level.
    Each transition:
        At a time, move only one wheel and the digit can go +1/-1 in either direction.
*/
class Solution {
public:
    int bfsSol(vector<string>& deadends, string target) {
        // Add all the deadends as the visited combinations
        unordered_set<string> visited(deadends.begin(), deadends.end());
        vector<int> MOVES = {1, -1};
        int level = 0, level_nodes = 1;
        queue<string> q;
        
        // Start combination itself is deadend
        if(visited.count("0000"))
            return -1;
        
        q.emplace("0000");
        visited.emplace("0000");
        
        while(!q.empty()) {
            auto cmb = q.front();
            q.pop();
            --level_nodes;
            
            // target reached
            if(cmb == target)
                return level;
            
            // For each wheel, try a different slot
            for(int wheel = 0; wheel < 4; wheel++) {
                // next lock combination
                string next_cmb(cmb);
                
                // Turn the wheel either up or down, i.e either it will have
                // the next or previous number
                for(auto move: MOVES) {
                    int digit = cmb[wheel] - '0';
                    digit += move;
                    
                    // Wrap the digit if needed, we could used this formula as well
                    // new_digit = (digit - delta + num_digits) % num_digits,
                    // Eg (0 - 1 + 10) % 10 = 9
                    if(digit == -1) digit = 9;
                    if(digit == 10) digit = 0;
                    // place the new digit
                    next_cmb[wheel] = digit + '0';
                    
                    // check if the new combination is visited or not
                    if(!visited.count(next_cmb)) {
                        visited.emplace(next_cmb);
                        q.emplace(next_cmb);
                    }
                }
            }
            
            // end of level
            if(level_nodes == 0) {
                ++level;
                level_nodes = q.size();
            }
        }
        return -1;
    }
    
    int openLock(vector<string>& deadends, string target) {
        return bfsSol(deadends, target);
    }
};
