/*
    https://practice.geeksforgeeks.org/problems/inversion-of-array/0/
    
    TC: O(NlogN)
*/
#include <bits/stdc++.h>
using namespace std;

long long countInversions(vector<int>& nums, int left,
                int mid, int right) {
    long long inversions = 0;
    int i = left, j = mid + 1;
    vector<int> temp;
    
    while(i <= mid && j <= right) {
        // If the element from 
        // left side is greater than one from right
        // side, then all the elements in first
        // array also count as an inversion
        if(nums[i] <= nums[j])
            temp.emplace_back(nums[i++]);
        else {
            temp.emplace_back(nums[j++]);
            inversions += mid - i + 1;
        }
    }
    while(i <= mid)
        temp.emplace_back(nums[i++]);
    while(j <= right)
        temp.emplace_back(nums[j++]);
    
    for(int i = 0; i < right - left + 1; i++) {
        nums[left + i] = temp[i];
    }
    return inversions;
}

// We count the inversions in the merge step of
// merge sort
long long solve(vector<int>& nums, int l, int r) {
    if(l < r) {
        int mid = l + (r - l) / 2;
        auto left_inv = solve(nums, l, mid);
        auto right_inv = solve(nums, mid + 1, r);
        return left_inv + right_inv + 
            countInversions(nums, l, mid, r);
    }   
    return 0;
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
            
        cout << solve(nums, 0, nums.size()-1)<< endl;
    }
	return 0;
}