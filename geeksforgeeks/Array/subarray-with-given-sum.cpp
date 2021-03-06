/*
    https://practice.geeksforgeeks.org/problems/subarray-with-given-sum/0
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include <bits/stdc++.h>
using namespace std;

// Using hashing
vector<int> checkSubarraySum(vector<int>& nums,
                            int& k) {
    unordered_map<int, int> sum_pos;
    vector<long long> sum(nums.size(), 0);
    
    int curr_sum = 0;
    sum_pos[0] = -1;

	for(int i = 0; i < nums.size(); i++) {
	    curr_sum += nums[i];
	    // Cummulative sum
	    sum[i] = curr_sum;
	    // check if the remainder for the current
	    // sum was seen before, if it was seen before 
	    // it means, in between there is a subarray sum which
	    // is a multiple of k
	    int remainder = curr_sum % k;
	    if(sum_pos.count(remainder)) {
	        // check if the subarray sum is k
	        int subarray = sum_pos[remainder] == -1 ? sum[i] : sum[i] - sum[sum_pos[remainder]];
	        if(subarray == k)
	            return vector<int>{sum_pos[remainder] + 1 + 1, i + 1};
	    }
	    // since there are only +ve nums, that means
	    // older index will make the sum greater
	    sum_pos[remainder] = i;
	}
	
    return vector<int>{-1};
}

/// Sliding Window (Works for +ve nums only)
// TC: O(N), SC: O(1)
vector<int> slidingWindow(vector<int>& arr, int &k) {
    int i = 0, j = 0;
    long long curr_sum = 0;
    
    while(i < arr.size()) {
        // expand the window
        if(curr_sum < k)
            curr_sum += arr[i++];
        // make the window valid
        // Since there are only +ve nums, 
        // If the current window size is more
        // then unless we remove numbers we won't
        // have a change to get a sum = k
        while(curr_sum > k)
            curr_sum -= arr[j++];
            
        if(curr_sum == k)
            return vector<int>{j+1, i};
    }
    return vector<int>{-1};    
}

int main()
{
    int t, n, k;
    cin >> t;
    while(t--) {
        cin >> n >> k;
        vector<int> nums(n);
        
        for(int i = 0; i < n; i++)
            cin >> nums[i];
            
        //auto indices = checkSubarraySum(nums, k);
        auto indices = slidingWindow(nums, k);
        if(indices.size() == 2)
            cout << indices[0] << " " << indices[1] << endl;
        else
            cout << indices[0] << endl;
    }
	return 0;
}