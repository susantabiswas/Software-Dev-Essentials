class Solution {
public:
    // Solution using bitset
    // Basically we use bitset array and apply shift operation for all the 
    // elements of array. Initially only 0th pos is achievable so it is set, then 
    // as we keep adding more numbers we shift the already added numbers by that amount.
    /* Eg: ini: 00000001
            num: 3, shift bits array by 3, which makes 0 + 3
            00000001 << 3 ==> 00001000, then take the OR with prev ==> 00001001
            num: 2, shift bits array by 2, which makes 0 + 2, 3 + 5, so both 2 and 5 will be marked
            00101201
    */
    // Since the sum in the two subsets needs to be same, that is basically saying 
    // the sum of each set should be half of total sum, we check in the end if the
    // half of total sum is possible
    
    // TC: O(N*b), b: no. of bits in the bitset, N: array length
    bool canPartitionBitset(vector<int>& nums) {
        // take total sum of all elements
        int total = accumulate(nums.begin(), nums.end(), 0);
        
        // if the total is odd, then paritioning is not possible
        if(total % 2 != 0)
            return false;
        
        bitset<100 * 200 + 1> bits;
        // zero sum can be achieved with null set
        bits[0] = 1;
        for(const int& num : nums)
            bits = bits | bits << num;
        // check if total/2 is achievable or not
        return bits[total >> 1];
    }
    
    // solution using DP
    bool canPartitionDPTabular(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        
        // odd sum can't be partitioned
        if(total % 2 != 0)
            return false;
        
        // each entry 'i': sum i can be formed by subsets of elements
        vector<bool> dp(total/2 + 1, false);
        // sum of zero is always possible
        dp[0] = true;
        // Since this uses 1D DP state, it is imp to make sure that for amount i,
        // we see the contributing numbers only once as it is like a 0-1 knapsack problem.
        for(const int& num : nums) { // ensures for numbers are not repeated
            for(int i = total / 2; i >= 1; i--) {   
                // since end goal is to get total/2 dp state,
                // so starting from end ensures that nums contributing to smaller number are not repeated
                // for larger numbers, like num 3 used for sum 3, and also for sum = 6(3 + 3) 
                int req_val = i - num;              
                if(req_val >= 0)
                    dp[i] = dp[i] || dp[req_val];
            }
        }
        return dp[total/2];
    }
    
    bool canPartition(vector<int>& nums) {
        return canPartitionDPTabular(nums);
        //return canPartitionBitset(nums);
    }
};
