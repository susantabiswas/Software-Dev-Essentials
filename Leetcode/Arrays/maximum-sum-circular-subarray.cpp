/*
	https://leetcode.com/problems/maximum-sum-circular-subarray/
	
    The max sum can either be in [0:N] or can start from somewhere in
    between 'j' and roll over from end to somewhere before 'j'. 
    For handling the first case, normal Kadane's algo is enough.
    For the second case, we can do total - min_sum
    
    If we want to divide the array in two parts, maxsum and minsum.
    naturally all the net negative subarray will go to minsum and net +ve
    to maxsum.
    
    A(+ve) + B(-ve) + C(max neg sing num)
    if A + B = +ve then gets added to maxSum because +ve + +ve > original number
    if A + B = -ve then added to minSUm, since -ve + -ve < original number
    
    TC: O(N),
    SC: O(1)
*/
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& arr) {
        if(arr.empty())
            return 0;
        
        int total = arr[0];
        int min_sum = arr[0], max_sum = arr[0];
        int curr_max = arr[0], curr_min = arr[0];
        
        for(int i = 1; i < arr.size(); i++) {
            curr_max += arr[i];
            curr_max = max(curr_max, arr[i]);
            curr_min += arr[i];
            curr_min = min(curr_min, arr[i]);
            max_sum = max(max_sum, curr_max);
            min_sum = min(min_sum, curr_min);
            
            total += arr[i];
        }
        
        // sum when the subarray rolls over from end to the start of array
        int circular_sum = total - min_sum;
        
        // if all the numbers are -ve, then total-min = 0, 
        // then the entire array is covered in min_sum, max_sum = -ve and circular_sum = 0, 
        // max of them will return 0, which is wrong, so we return max_sum in this case
        return max_sum > circular_sum ? max_sum : circular_sum == 0 ? max_sum : circular_sum;
    }
};
