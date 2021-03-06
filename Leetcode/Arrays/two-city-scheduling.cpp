/*
    https://leetcode.com/problems/two-city-scheduling/
    
    TC: O(NlogN)
*/

class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        // For each person, we need to know whether it is better to send 
        // him to A or B. To know this we compute the money lost for each person
        // if he is sent to A instead of B
        vector<int> loss(costs.size(), 0);
        // Savings when a person travels to A instead of B
        int total_cost = 0;
        for(int i = 0; i < costs.size(); i++) {
            total_cost += costs[i][0];
            loss[i] = costs[i][0] - costs[i][1];
        }
        // sort the loss in decreasing order, when cost A < cost B, it 
        // is negative, meaning it is better to send A than B.
        /// But when it is positive it means it is better to send to city B
        sort(loss.begin(), loss.end(), greater<>());
        // We send the n people with max loss to city B and remaining to city A
        for(int i = 0; i < costs.size()/2; i++) {
            total_cost -= loss[i];
        }
            
        return total_cost;
    }
};
