/*
    746. Min Cost Climbing Stairs
    https://leetcode.com/problems/min-cost-climbing-stairs/
    
    From a given index, we decide whether to take 1 or 2 steps based
    on the total cost incurred and select the min cost step.
*/
class Solution {
public:
    int minCostMem(int curr, vector<int>& dp, vector<int>& cost) {
        // reached the top
        if(curr >= cost.size())    
            return 0;
        if(dp[curr] == -1) {
            dp[curr] = cost[curr] + min(minCostMem(curr + 1, dp, cost),
                                       minCostMem(curr + 2, dp, cost));
        }
        return dp[curr];
    }
    
    int minCostTab(vector<int>& dp, vector<int>& cost) {
        // only one step or 0 step
        if(cost.empty() || cost.size() == 1)
            return cost.empty() ? 0 : cost[0];
        
        // dp[i] = min cost to use the curr step ( includes reaching the step + using the step)
        dp[0] = cost[0], dp[1] = cost[1];
        
        for(int i = 2; i < cost.size(); i++) {
            dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
        }
        return min(dp[cost.size() - 1], dp[cost.size() - 2]);
    }
    
    int mem(int n, vector<int>& costs, vector<int>& dp) {
        if(n == 0)
            return dp[n] = costs[n];
        if(dp[n] == -1) {
            dp[n] = costs[n] + min(n-1 >= 0 ? mem(n-1, costs, dp) : 0,
                                  n-2 >= 0 ? mem(n-2, costs, dp) : 0);
        }
        return dp[n];
    }
    
    int minCostClimbingStairs(vector<int>& cost) {
        // dp[i] = Min cost to reach the top of stairs from ith pos
        vector<int> dp(cost.size(), -1);
        // return min(minCostMem(0, dp, cost), minCostMem(1, dp, cost));
        // return minCostTab(dp, cost);

        // Way 3
        mem(cost.size()-1, cost, dp);
        return min(dp[cost.size()-2], dp[cost.size()-1]);
    }
};