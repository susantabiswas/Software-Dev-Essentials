/*
    https://leetcode.com/problems/last-stone-weight-ii/
    TC: O(n * S), S: total sum of elements
    SC: O(S)
    
    This problem can be transformed to another problem, it is 494. Target Stone problem on LC.
    Here we need to smash the rocks to get the min final weight. The thing to note here is the order
    in which the stones can be smashed. The problem looks like a simulation problem where you need to push the
    new smashed weight and run the simulation till we have only one or zero rock. But another way of thinking
    is that if we can group the stones in two groups such that diff of the two groups is min, then also the
    problem is solved. Everytime we get |x -y| the extra weight is nothing but the surplus diff in x and this diff
    is used in the next iteration of simulation. So by forming two max groups P and N, we also account for the surplus of each stone in the group only and when they are smashed the net diff gives us the same effect as simulation.
    
    So the problem in hand: P - N = Target(T)
    We try to maximize both P and N to get the min T.
    This can be done using DP.
    
    P - N = T
    2P - P - N = T
    2P = T + S, sum(S) = N + P
    
*/

class Solution {
public:
    int lastStoneWeightTabular(vector<int>& stones){
        // calculate the sum of all values
        int total = accumulate(stones.begin(), stones.end(), 0);
        int min_weight = total;
        
        // dp(i): can P with sum 'i' be formed 
        vector<bool> dp(total/2 + 1, false);
        //getting a sum of zero is always possible
        dp[0] = true;
        
        for(const int& stone: stones) {
            for(int i = total/2; i >= stone; i--) {
                dp[i] = dp[i] || dp[i - stone];
                
                // 2P = T + S, we need to find min(T)
                int target = abs(2*i - total);
                if(dp[i])
                    min_weight = min(min_weight, target);
            }
        }
        
        return min_weight;
    }
    
    // driver 
    int lastStoneWeightII(vector<int>& stones) {
        return lastStoneWeightTabular(stones);
    }
};
