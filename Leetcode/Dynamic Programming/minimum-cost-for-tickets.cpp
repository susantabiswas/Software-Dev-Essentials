/*
    https://leetcode.com/problems/minimum-cost-for-tickets/submissions/
*/
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        vector<int> dp(30, 0);
        int min_cost = 0;
        unordered_set<int> s(days.begin(), days.end());
        
        // dp[i] is cost till ith day, dp[1] is cost on 1st day
        for(int i = 1; i <= 366; i++) {
            // non travelling day
            if(s.find(i) == s.end())
                dp[i % 30] = dp[(i-1) % 30];
            else
                dp[i % 30] = min({dp[(i-1) % 30] + costs[0], 
                             dp[(max(0, i - 7)) % 30] + costs[1],
                             dp[(max(0, i - 30)) % 30] + costs[2]});
        }
        return dp[days.back() % 30];
    }
};
