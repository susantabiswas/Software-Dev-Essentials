/*
    https://practice.geeksforgeeks.org/problems/missing-number-in-array/0
*/
#include <bits/stdc++.h>
using namespace std;

int solve(vector<int>& nums) {
    long long range_xor = 0, nums_xor = 0;
    const int N = nums.size() + 1;
    
    for(int i = 1; i <= N; i++) {
        range_xor ^= i;
    }
        
    for(const int &num: nums)
        nums_xor ^= num;
    return range_xor ^ nums_xor;
}

int main()
{
    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        vector<int> nums(n-1);
        
        for(int i = 0; i < n-1; i++)
            cin >> nums[i];
            
        cout << solve(nums) << endl;
    }
	return 0;
}