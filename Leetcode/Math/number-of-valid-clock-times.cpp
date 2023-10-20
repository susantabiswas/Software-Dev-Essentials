/*
    https://leetcode.com/problems/number-of-valid-clock-times/
    
    Hour time just depends on the 1st 2 chars and mins time depends only on the
    last two chars.
    
    For hour and mins sections:
    - Find the possible values for the 1st and 2nd digits
    
    Then just form all the numbers and check if they are valid for that section
    TC: O(1)
*/
class Solution {
public:
    int ways(vector<int>& cand1, vector<int>& cand2, int low, int high) {
        int poss = 0;
        
        for(auto n1: cand1)
            for(auto n2: cand2) {
                int num = n1 * 10 + n2;
                if(num >= low && num <= high)
                    ++poss;
            }
        
        return poss;
    }
    
    int countTime(string time) {
        vector<int> first, second, third, fourth;
        
        // Extract the possible values for each of the sections
        // Hour time depends only on the 1st 2 chars
        if(time[0] == '?')
            first = {0, 1, 2};
        else
            first = {time[0] - '0'};
        
        if(time[1] == '?')
            second = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        else
            second = {time[1] - '0'};
        
        // Mins time only depends on the last 2 chars
        if(time[3] == '?')
            third = {0, 1, 2, 3, 4, 5};
        else
            third = {time[3] - '0'};
        
        if(time[4] == '?')
            fourth = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        else
            fourth = {time[4] - '0'};
        
        return ways(first, second, 0, 23) * ways(third, fourth, 0, 59);
    }
};
