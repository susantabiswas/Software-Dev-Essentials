/*
    https://leetcode.com/problems/maximum-average-subarray-i/
    
    Using sliding window, find the sum of k sized windows, and check if 
    the avg for current window is the max. This is repeated for each k sized windows.
*/
class Solution {
public:
    double findMaxAverage(vector<int>& arr, int k) {
        if(arr.empty())
            return 0;
        
        double max_avg = INT_MIN, curr_avg = 0;
        // calculate the avg of 1st window of size K
        for(int i = 0; i < k; i++)
            curr_avg += arr[i];
            
        // now process each window of size k and update max seen avg
        for(int i = 0; i < arr.size() - k; i++) {
            max_avg = max(max_avg, curr_avg / k);
            // remove the 1st element of current window and add the next element 
            curr_avg = curr_avg - arr[i];
            curr_avg = curr_avg + arr[i + k];
        }
        max_avg = max(max_avg, curr_avg / k);
        
        return max_avg;
    }
};
