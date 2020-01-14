/*
    https://leetcode.com/problems/next-permutation/
    
    TC: O(N), SC: O(1)
    
    Next pmt is basically finding the next bigger number formed by combining the numbers together.
    So everytime a number just greater than the previous number is required. So in the final state
    the arrangement of numbers will be such that all the numbers will be arranged in descending order,
    since that combination will give the largest number. 
    Now for any intermediate number, the next greater number can be formed by finding the first number
    position 'i' that is not following descending order, meaning we can make a greater number just by replacing
    the number with a greater number in that position. So we start searching from N-1 for a number greater than 
    current number nums[i] at pos 'i' that was found not to follow the order, say we found it at 'j', then just swap the numbers. 
    
    Reverse all the numbers in nums[i+1 : N-1],
    Since everything before swapping was in descending order in [i+1:N-1] range,
    so after swapping a smaller number with the smallest in the descending order will
    make a new pmt where everything after i+1 is biggest possible pmt, so to make it the smallest
    pmt, reverse the numbers so that smallest comes before the larger numbers making the pmt smallest
    possible with the swapped numbers
    
*/
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // find the first number it that is smaller than its next number
        int i = nums.size() - 2;
        while(i >= 0 && nums[i] >= nums[i+1])
            --i;
        // every number is in descending order, so no next pmt exists
        // return the ascending sorted order
        if(i < 0) {
            reverse(nums.begin(), nums.end());
            return;
        }
        
        // for the current position, swap it with the first number that is bigger
        int j = nums.size() - 1;
        while(i >= 0 && j > i) {
            if(nums[j] > nums[i]) {
                swap(nums[i], nums[j]);
                // Reverse all the numbers in nums[i+1:N-1],
                // Since everything before swapping was in descending order in [i+1:N-1] range,
                // so after swapping a smaller number with the smallest in the descending order will
                // make a new pmt where everything after i+1 is biggest possible pmt, so to make it the smallest
                // pmt, reverse the numbers so that smallest comes before the larger numbers making the pmt smallest
                // possible with the swapped numbers
                reverse(nums.begin() + i + 1, nums.end());
                break;
            }
            --j;
        }
    }
};
