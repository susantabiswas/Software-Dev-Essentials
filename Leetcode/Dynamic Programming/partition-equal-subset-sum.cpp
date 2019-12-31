/*
    https://leetcode.com/problems/partition-equal-subset-sum/
*/
class Solution {
public:
    // Solution using bitset
    // Basically we use bitset array and apply shift operation for all the 
    // elements of array.
    // Since the sum in the two subsets needs to be same, that is basically saying 
    // the sum of each set should be half of total sum, we check in the end if the
    // half of total sum is possible
    bool canPartitionBitset(vector<int>& nums) {
        // take total sum of all elements
        int total = accumulate(nums.begin(), nums.end(), 0);
        
        // if the total is odd, then paritioning is not possible
        if(total % 2 != 0)
            return false;
        
        bitset<100 * 200 + 1> bits(1);
        for(const int& num : nums)
            bits = bits | bits << num;
        
        return bits[total >> 1];
    }
    
    // solution using DP
    bool canPartitionDPTabular(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        
        // odd sum can't be partitioned
        if(total % 2 != 0)
            return false;
        
        // each entry 'i': sum i can be formed by subsets of elements
        vector<bool> dp(nums.size() + 1, false);
        // sum of zero is always possible
        dp[0] = true;
        /*
        constructing sum/2 to 1, constructing
        this way can avoid addition of redundant terms in some problems
        for(const int& num: nums) {
            // we need to check if sum 'i' is possible 
            for(int i = total / 2; i >= 1; i++) {
                dp[i] = dp[i] || dp[i - num];
            }
        }
        */
        // constructing dp from 1 to sum/2
        for(int i = 1; i <= total / 2; i++) {
            for(const int& num : nums) {
                int req_val = i - num;
                if(req_val >= 0)
                    dp[i] = dp[i] || dp[req_val];
            }
        }
        return dp[nums.size()];
    }
    
    bool canPartition(vector<int>& nums) {
        return canPartitionBitset(nums);
    }
};
