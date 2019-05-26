/*
    746. Min Cost Climbing Stairs
    https://leetcode.com/problems/min-cost-climbing-stairs/
    
    From a given index, we decide whether to take 1 or 2 steps based
    on the total cost incurred and select the min cost step.
*/
class Solution {
public:
    int minCostClimb(int curr, vector<int>& cost, vector<int>& dp) {
        // once we reach beyond the last step, our goal is reached
        if(curr >= cost.size())
            return 0;
        
        // at current step, we select the step which gives us the min overall cost
        if(dp[curr] == 0) {
            dp[curr] = min(minCostClimb(curr + 1, cost, dp), 
                        minCostClimb(curr + 2, cost, dp)) 
                        + cost[curr];
        }
        return dp[curr];
    }
    
    /*
        Stair top can be reached either from N-1 or N-2th step. That means
        we need to find the min cost incurred while selecting a step. 
        So for each step we find the cost incurred when it is used,
        which is cost of current step and min cost to reach current step.
    */
    int minCostClimbTab(vector<int>& cost, vector<int>& dp) {
        if(cost.empty()) 
            return 0;
        if(cost.size() == 1) 
            return cost[1];
        
        dp[0] = cost[0];
        dp[1] = cost[1];
        
        for(int i = 2; i < cost.size(); i++) 
            // calculate the cost incurred for selecting current:
            // which is cost of current step and min cost to reach current step
            dp[i] = min(dp[i-1], dp[i-2]) + cost[i];
        
        return min(dp[cost.size() - 1], dp[cost.size() - 2]);
    }
    
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> dp(cost.size(), 0);
        // take the min out of starting at 0 and 1th step
        //return min(minCostClimb(0, cost, dp), minCostClimb(1, cost, dp));
        
        return minCostClimbTab(cost, dp);
    }
};
