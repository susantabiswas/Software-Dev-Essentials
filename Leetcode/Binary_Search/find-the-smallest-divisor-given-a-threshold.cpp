/*
    https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/
    
    The problem can be solved using binary search. The thing to note here
    is we do binary search on the search space of solution, instead of doing it on 
    the array numbers. 
    We start by setting the min and max solution limits, then try to prune the
    search space. Each time we compute the mid and check if the sum <= threshold,
    if it is that means, the divisor value is probably on the left side and exclude the
    entire right side, similar argument for the right side prunning.
    
    TC: O(Nlog(INT_MAX))
*/

class Solution {
public:
    long long divSum(vector<int> &nums, int div) {
        long long sum = 0;
        for(auto &num: nums) {
            sum += (num - 1) / div + 1; // formula for finding ceil
            //sum += max((double)1, ceil((double)num / div)); // does the same thing
        }
        return sum;
    }
    
    int smallestDivisor(vector<int>& nums, int threshold) {
        
        long long low = 1, high = INT_MAX;
        while(low < high) {
            long long mid = low + (high - low) / 2;
            
            long long sum = divSum(nums, mid);
            // Since current divisor gives a bigger sum, no point
            // looking at the left
            if(sum > threshold)
                low = mid + 1;
            // the numbers of left including the mid are potential ans
            else
                high = mid;
        }
        
        return high;
    }
};
