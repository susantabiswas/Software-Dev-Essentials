/*
    https://practice.geeksforgeeks.org/problems/count-the-triplets/0
    
    https://www.geeksforgeeks.org/find-triplet-sum-two-equals-third-element/
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include <bits/stdc++.h>
using namespace std;

/// Using two pointers
// TC: O(nlogn)
int findTriplets(vector<int>& nums) {
    int ans = 0;
    sort(nums.begin(), nums.end());
    
    // a + b = c
    // nums[i] will be c 
    for(int c = nums.size() - 1; c >= 0; c--) {
        int a = 0, b = c - 1;
        while(a < b) {
            int sum = nums[a] + nums[b];
            if(sum == nums[c]) {
                ++ans;
                ++a, --b;
            }        
            else if(sum < nums[c])
                ++a;
            else
                --b;
        }
    }
    return ans == 0 ? -1 : ans;
}

int main()
{
    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        vector<int> nums(n);
        
        for(int i = 0; i < n; i++)
            cin >> nums[i];
            
        cout << findTriplets(nums) << endl;
    }
	return 0;
}