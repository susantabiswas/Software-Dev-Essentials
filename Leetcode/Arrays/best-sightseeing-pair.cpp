/*
    https://leetcode.com/problems/best-sightseeing-pair/
    
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        if(values.empty())
            return 0;
        // for any value[i], it can form the largest value 
        // pair with the biggest value out of all the sightseeing spots
        // but we also need to account for the subtraction of distance gap.
        // So we can scan for the max value seen so far and to account for gap, 
        // we decrease its value by 1 when moving forward, this will simulate the effect of 
        // the max value moving away from its position towards curr position j
        
        // scan from left to right
        int max_so_far = 0, max_pair = 0;
        for(int i = 0; i < values.size(); i++) {
            max_pair = max(max_pair, values[i] + max_so_far);
            // -1 to account for forward movement, as gap is subtracted each time
            max_so_far = max(max_so_far-1, values[i]-1);
        }
        return max_pair;
    }
};
