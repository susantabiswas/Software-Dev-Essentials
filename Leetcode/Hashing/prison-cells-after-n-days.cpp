/*
    https://leetcode.com/problems/prison-cells-after-n-days/submissions/
    
    Since for binary bits, there can be 2^N combinations. So since only 6 places
    change, we have 2^6 combinations and for any N greater than that, we will see
    repeatition. The possible states can be thought of like values on a circle, so we start
    with the state after the initial as the starting point, since initial state can have
    1 in 1st or last position and because of the rules we will never get that state and 
    simulation won't end. 
    So when we again see a value which matches our first state, means we have covered the possible states
    and the answer is amongst them.
    so we use (N-1) % len(states). N-1 so that it matches the array index.
    
    TC: O(2^8)
*/
class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        if(N <= 0)
            return cells;
        
        // This stores the sequential states
        vector<vector<int>> states;
        vector<int> curr_state(cells.size(), 0), prev_state = cells;
        
        // Since there are fixed number of states, so many states will repeat
        for(int i = 0; i < N; i++) {
            for(int j = 1; j < cells.size() - 1; j++)
                // since 1st and last don't have adjacent, so it is 0
                curr_state[j] = prev_state[j-1] == prev_state[j+1];
            
            // check if the current state is one which has been seen before
            // so we completed the cycle and we know the upcoming states
            if(!states.empty() && states[0] == curr_state)
                return states[(N-1) % states.size()];
            
            states.emplace_back(curr_state);
            prev_state = curr_state;
        }
        
        return curr_state; 
    }
};
