/*
    https://practice.geeksforgeeks.org/contest-problem/perfect-pair-sum/1/
    
    Two elements 'a' and 'b' are said to be a perfect pair if sum of digits of
    'a' is equal to sum of digits of 'b'. Find the perfect pair with the maximum sum (a+b). 

*/

// Finds the sum of digits of a number
int digitSum(int num) {
    int sum = 0;
    while(num) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

// TC: O(N)
// SC: O(N)
int PerfectMatch(vector<int> arr, int n) 
{
    int max_sum = -1;
    // (digit sum, number)
    unordered_map<int, int> digit_sum;
    
    for(int& num: arr) {
        int sum_of_digits = digitSum(num);
        // check if there exists a number seen before with same digit sum
        if(digit_sum.count(sum_of_digits)) {
            // update the max sum
            max_sum = max(max_sum, digit_sum[sum_of_digits] + num);
            // If the current number > then exiting number for the same sum
            if(digit_sum[sum_of_digits] < num)
                digit_sum[sum_of_digits] = num;
        }
        else {
            digit_sum.emplace(sum_of_digits, num);
        }
    }
    return max_sum;
}