/*
    https://practice.geeksforgeeks.org/problems/sort-an-array-of-0s-1s-and-2s/0
*/

#include <bits/stdc++.h>
using namespace std;

void solve(vector<int> &nums) {
    vector<int> freq(3, 0);
    for(const int& num: nums)
        freq[num] += 1;
        
    // We do it in place
    for(int i = 0, j = 0; i < freq.size() && j < nums.size();
        i++) {
        while(freq[i]--) 
            nums[j++] = i;
    }
    
    for(const int& num: nums)
        cout << num << " ";
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
            
        solve(nums);
        cout << endl;
    }
	return 0;
}