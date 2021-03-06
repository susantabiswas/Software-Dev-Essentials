/*
    https://practice.geeksforgeeks.org/editorial.php?pid=702326
    
    Idea is to keep track of cummulative sum and also the
    remainder at each position with k for sum till that point.
    When we see the same remainder, that means there was a factor 
    of k in between the two positions.
    TC: O(N)
*/

//User function Template for C++
int maxNumOfChocolates(int arr[], int n, int k) 
{ 
    // We keep track of cummulative window and check
    // for max window sum which is a multiple of k
    unordered_map<int, int> sum_pos;
    // Cummulative sum
    vector<int> cumm_sum(n, 0);
    int max_sum = 0, curr_sum = 0;
    
    // Initial sum 0
    sum_pos[0] = -1;
        
    for(int i = 0; i < n; i++) {
        curr_sum += arr[i];
        cumm_sum[i] = curr_sum;
        
        if(sum_pos.count(curr_sum % k)) {
            int subarray = i == 0 ? cumm_sum[i] : cumm_sum[i] - cumm_sum[sum_pos[curr_sum % k]];
            max_sum = max(max_sum, subarray);
        }
        // if the remainder exists or not
        else 
            sum_pos[curr_sum % k] = i;
    }
    
    return max_sum / k;
} 