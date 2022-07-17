/*
    https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/
    
    TC: O(N * logM), M = Max number, N = No. of numbers
    SC: O(N), worst case each digit sum is unique
    
    Idea is to keep save the digit sum in a hash table along side the max number for that sum.
    For each numbe, check if there is another number with the same digit sum, then check if the
    pair makes the largest sum or not
*/
class Solution {
public:
    // TC: O(log(num))
    int sumOfDigits(int num) {
        int sum = 0;
        while(num) {
            sum += num % 10;
            num /= 10;
        }    
        return sum;
    }
    
    int maximumSum(vector<int>& nums) {
        int max_sum = -1;
        // <Sum of digits, max number with this sum>
        unordered_map<int, int> digit_sum;
        
        // For each number, check if there is a number seen with the same sum
        // If yes, then track if it is the highest sum of numbers seen so far.
        for(auto num: nums) {
            // Find the sum of digit
            int sum = sumOfDigits(num);
            // If the current pair has more sum than the max tracked sum, update it
            if(digit_sum.count(sum) && digit_sum[sum] + num > max_sum)
                max_sum = digit_sum[sum] + num;
            // We only need to save the max number with a current sum to increase the odds
            digit_sum[sum] = max(digit_sum[sum], num);
        }
        return max_sum;
    }
};
