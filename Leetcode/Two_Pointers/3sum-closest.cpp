/*
    https://leetcode.com/problems/3sum-closest/
    
    We have the eq: Ai + Aj + Ak = T
    Core problem is to find cmb of Ai, Aj and Ak that sums up to T or the
    one closest. Essentially we can treat this problem as 3Sum problem where 
    we find whether it is possible to have a triplet equal to target. While doing 
    our search for each triplet we also track how far is it from the target. At the end
    if we are unable to find a matching triplet, just return the one closest.
    
    I have given two styles of doing it, both use fundamentally the same logic.
*/
class Solution {
public:
    // Solution 1: Two pointers + Sorting
    // TC: O(nlogn + n^2)
    int sol1(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        // Tracks the min diff of a sum from target found so far
        int min_diff = INT_MAX, closest = INT_MAX;
        
        // Fix Ai
        for(int i = 0; i < n; i++) {
            int j = i + 1, k = n-1;
            // Optimize Aj and Ak such that Ai + (Aj + Ak) -> target
            while(j < k) {
                long sum = nums[i] + nums[j] + nums[k];
                // Find how far is the current sum
                int diff = abs(target - sum);
                if(diff < min_diff) {
                    min_diff = diff;
                    closest = sum;
                }
                // If current sum is equal to target, no need to process further
                if(sum == target)
                    return sum;
                else if(sum > target)
                    --k;
                else
                    ++j;
            }
        }
        return closest;
    }
    
    // Solution 2: Two pointers + Sorting
    // TC: O(nlogn + n^2)
    int sol2(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        // Tracks the min diff of a sum from target found so far
        int min_diff = INT_MAX, closest = INT_MAX;
        
        // Fix Ai
        for(int i = 0; i < n; i++) {
            int j = i + 1, k = n-1;
            // Optimize Aj and Ak such that the sum becomes equal to (target - Ai)
            long to_reach = target - nums[i];
            
            // Optimize Aj and Ak such that (Aj + Ak) -> (target - Ai)
            while(j < k) {
                long sum = nums[j] + nums[k];
                // Find how far is the current sum from (target - Ai)
                int diff = abs(sum - to_reach);
                // If current combination is closest to target, save the cmb
                if(diff < min_diff) {
                    min_diff = diff;
                    closest = sum + nums[i];
                }
                // If current sum is equal to target, no need to process further
                if(sum == to_reach)
                    return sum + nums[i];
                else if(sum > to_reach)
                    --k;
                else
                    ++j;
            }
        }
        return closest;
    }
    
    int threeSumClosest(vector<int>& nums, int target) {
        // return sol1(nums, target);
        return sol2(nums, target);
    }
};
