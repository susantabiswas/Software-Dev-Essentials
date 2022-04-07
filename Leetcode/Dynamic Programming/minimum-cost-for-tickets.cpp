/*
    https://leetcode.com/problems/minimum-cost-for-tickets/submissions/

    Idea is for any day, we just need to find out which pass is most suitable for
    that day. For deciding this, we don't consider the future days. Only check for past days
    in case any of the pass covers the past days as well. This can help optimize the cost
    of past travels as well.
    Eg travel_cost[i] = cost of 'j' pass days + travel_cost[i - j days].

    For a non-travel day the cost incurred for that is just equal to cost
    incurred till yesterday.

*/
class Solution {
public:
    // Sol 1
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        vector<int> dp(30, 0);
        int min_cost = 0;
        unordered_set<int> s(days.begin(), days.end());
        
        // dp[i] is total cost incurred till ith day, dp[1] is cost on 1st day
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

    // Sol 2
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        unordered_set<int> travel_days(days.begin(), days.end());
        // dp[i] = Min cost to travel on day 'i'
        vector<int> dp(366, 0);
        
        for(int day = 1; day < 366; day++) {
            // Only need a ticket if the current day is for travel
            if(travel_days.count(day))
                // While buying a ticket, we need not consider the future.
                // We consider which pass works the best if the last day of that pass
                // is used for travel on the curr day
                dp[day] = min({costs[0] + (day - 1 >= 0 ? dp[day - 1] : 0),
                              costs[1] + (day - 7 >= 0 ? dp[day - 7] : 0),
                              costs[2] + (day - 30 >= 0 ? dp[day - 30] : 0)
                               });
            else
                dp[day] = dp[day - 1];
        }
        return dp[days.back()];
    }
};
