/*
    https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
*/
class Solution {
public:
    // Bitmask solution
    // TC: O(2^n * n)
    // SC: O(2^n)
    /*
        The core idea here is transitioning of states. A state here is a selection of elements, where some have formed proper
        partitions with req target sum and some might be there in the current subset which have not yet reached the target.
        We start with an empty set and keep adding one element at a time to the set, then repeat the process of adding element to existing 
        subsets. The goal here is to see whether we can reach the final selection state (where all elements have been picked) from 
        initial empty set while obeying certain state transition rules.
        
        We use bitmask for storing the state of elements in an efficient way. We use dp cache to save the outcome of selection of 
        certain elements. dp[mask] = sum of elements that are left out after trying to create proper partitions with target sum. 
        For a given selection mask, we might have already formed proper subsets with req target and currently in the process of 
        filling the current subset. That is why in the end we check dp[(1 << N) - 1] == 0, this tells whether we were able to 
        put the elements into partitions with target sum and no elements are left.
        
        dp[mask | (1 << i)] = (dp[mask] + nums[i]) % target
        Above step is basically what happens when we add nums[i] to current subset, either it completes the subset and reaches target sum 
        leaving no remainder sum => dp[mask | (1 << i)] = 0
        Or it still is short of some amount and dp[mask | (1 << i)] = remainder sum in current subset.
        
        Let's say final state is dp[111]
        Now for transition to this state 3 states will be used: dp[011], dp[101] and dp[110]. 
        We will try to add the elements which have still not been picked in these selection states and check which of the existing subset selection
        can help reach the final state where all the elements have been put in some partition.
    */
    bool bitMaskSol(vector<int>& nums, int k) {
        // sum of all elements
        long sum = accumulate(nums.begin(), nums.end(), 0);
        const int N = nums.size();
        
        // if the total sum can't be equally divided into k partitions
        // or if more number of partitions than total number of elements
        if(sum % k || k > N)
            return false;
        // Find the sum each partition needs to attain
        int target = sum / k;
        
        // (1 << N): power set for the subsets of curr array, since
        // there are N elements, we need N bits to represent all the elements in a mask
        // Mask: A N-bit mask is a representation of elements picked in subsets, eg: 0101 => {nums[2], nums[0]}
        // A mask can contain info about multiple subsets, eg mask = 101101, and dp[101101] = 2, means
        // that the current selection of elements have formed complete paritions with req sum say 
        // 1011xx indicates that there are 2 subsets (1xxxxx and xx11xx) with req target and currently we are filling the
        // subset which has xxxxx1.
        // dp[mask]: (Total sum of all elements represented in the mask) % Target,
        // when dp[mask] = 0, it shows that given mask elements have partitions with Target sum and 
        // there are no remainder (extra) elements wrt target sum.1
        vector<int> dp((1 << N) + 1, -1);
        // empty set can be partitioned
        dp[0] = 0;
        
        for(int mask = 0; mask < (1 << N); mask++) {
            // if current subset is not valid, since we are marking
            // bits acc. to position of an elements, so we might not be able to set
            // each possible bit mask. eg: [4,3,2,3,5,2,1], k = 4 => target=5
            // means (4,3) can't be put in a subset => 011 won't be processed and hence dp[011] = -1
            if (dp[mask] == -1) 
                continue; 
            for(int i = 0; i < N; i++) {
                // If current element is not already picked or
                // if adding the curr element doesn't make sum > target for
                // the current subset
                if(!(mask & (1 << i)) && (dp[mask] + nums[i] <= target)) 
                    dp[mask | (1 << i)] = (dp[mask] + nums[i]) % target;
            }
        }
        // Since we used 0 indexed loop earlier, so (1<<i) actually represents 0 indexed positions
        // hence (2^N) - 1 is actually the one representing the selection of elements for 
        // N no. of elements. Eg: [1,3,2], n = 3,
        // 2^3 = 8(1000) (useful with 1 based indexing) , 2^3-1 = 7 (111) (0 based indexing)
        return dp[(1 << N) - 1] == 0;
    }
    
    // NOTE: TLE
    // TC: O(2^Nk), We spend max O(2^n) to find one partition, one that is done then we look for the
    // next parition which might again take O(2^n). Thing to note here is finding the next partition depends
    // on the computation and backtracking done previously, so (2^n * 2^n) not (2^n + 2^n)
    // Since we find k partitions, O(2^n * 2^n * 2^n ....... k times) ~ O(2^nk)
    // SC: O(n)
    bool backtrack(int curr, int sum, int k, int target,
                  vector<bool>& visited, vector<int>& nums) {
        // base case: single partition sum is always valid
        if(k <= 1)
            return true;
        // if current subset sum has reached target, we start picking elements for 
        // new subset
        if(sum == target)
            return backtrack(0, 0, k-1, target, visited, nums);

        // try adding the remaining elements. For each either include or exclude it
        for(int i = curr; i < nums.size(); i++) {
            if (visited[i] || sum + nums[i] > target) 
                continue;
            
            visited[i] = true;
            if(backtrack(i+1, sum + nums[i], k, target, visited, nums))
                return true;
            visited[i] = false;
        }
        return false;
    }
    
    // Backtracking solution
    bool backtrackSol(vector<int>& nums, int k) {
        vector<bool> visited(nums.size(), false);
        // sum of all elements
        long sum = accumulate(nums.begin(), nums.end(), 0);
        // Find the sum each partition needs to attain
        int target = sum / k;
        // if the total sum can't be equally divided into k partitions
        // or if more number of partitions than total number of elements
        if(sum % k || k > nums.size())
            return false;
        sort(nums.begin(), nums.end(), greater<>());
        return backtrack(0, 0, k, target, visited, nums);
    }
    
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        // return backtrackSol(nums, k);
        return bitMaskSol(nums, k);    
    }
};
