/*
    https://leetcode.com/problems/matchsticks-to-square/
    
    Core Idea: In order to get a square made, we need to ensure that we can group
    the sides such that there are 4 groups of same size (sum). This problem is basically
    equal sum k partition problem.
    
    Solution 1: Backtracking 
    We need to check if we can find 4 partitions with equal sum.
    
    Solution 2: Bitmask
    Here we use binary encoded representation to map selection of matchsticks.
    Mask: Current matchsticks chosen for selection. Some of them already are part of req 
    partition and there might be few in the current partition which still doesn't have total
    sum equal to req target sum.
    
    We use bitmasking to transition states starting with an empty subset and finally aim
    to reach the final state where all the matchsticks have been picked and put in some 
    partition.
    Here is explanation of the logic in more depth
    https://leetcode.com/problems/partition-to-k-equal-sum-subsets/discuss/1952411/C%2B%2B-Bitmasking-and-backtracking-solutions-Detailed-Explanation
*/
class Solution {
public:
    bool backtrack(int curr, int side_length, int partition,
                  int& target, vector<int>& nums, vector<bool>& visited) {
        // base case, when all paritions are done
        if(partition == 0)
            return true;
        if(side_length == target)
            return backtrack(0, 0, partition-1, target, nums, visited);
        
        // Try to fill the current partition with each of the matchstick sides
        for(int i = curr; i < nums.size(); i++) {
            // add the current side to curr partition only if it doesnt exceed target
            // and side has not been used yet
            if(!visited[i] && nums[i] + side_length <= target) {
                visited[i] = true;
                if(backtrack(i+1, side_length + nums[i], partition, target, nums, visited))
                    return true;
                visited[i] = false;
            }
        }
        return false;
    }
    
    // Backtracking solution
    // TC: O(2^4N), We spend O(2^n) for one partition, and do this 4 times: 2^n * 2^n .... 2^n
    bool backtrackSol(vector<int>& nums) {
        long sum = accumulate(nums.begin(), nums.end(), 0);
        // check if the total sum of side lengths can be divided into 4 equal partitions
        if(sum % 4)
            return false;
        // target side of square 
        int target = sum / 4;
        // keeps track of sides used
        vector<bool> visited(nums.size(), false);
        
        return backtrack(0, 0, 4, target, nums, visited);
    }
    
    // Bitmask solution
    // TC: O(N * 2^N)
    // SC: O(2^N)
    bool bitmaskSol(vector<int>& nums) {
        long sum = accumulate(nums.begin(), nums.end(), 0);
        // check if the total sum of side lengths can be divided into 4 equal partitions
        if(sum % 4)
            return false;
        
        // target side of square 
        int target = sum / 4;
        const int N = nums.size();
        // dp[mask] = total sum of elements for current partition, indicates if there is any remainder 
        // left for curr partition
        vector<int> dp((1<<N) + 1, -1);
        dp[0] = 0;
        
        // try out all the matchstick subset combinations
        for(int mask = 0; mask < (1 << N); mask++) {
            if(dp[mask] == -1)
                continue;
            // try adding unadded matchstick to the current subset partition
            for(int i = 0; i < nums.size(); i++) {
                // current element is already part of subset
                if(mask & (1 << i))
                    continue;
                if(nums[i] + dp[mask] <= target)
                    dp[mask | (1 << i)] = (dp[mask] + nums[i]) % target;
            }
        }
            
        return dp[(1<<N) - 1] == 0;
    }
    
    bool makesquare(vector<int>& matchsticks) {
        // return backtrackSol(matchsticks);
        return bitmaskSol(matchsticks);
    }
};
