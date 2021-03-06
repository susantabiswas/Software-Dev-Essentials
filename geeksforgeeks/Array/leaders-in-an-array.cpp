/*
    https://practice.geeksforgeeks.org/problems/leaders-in-an-array/0
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> solve(vector<int> &nums) {
    int largest = INT_MIN;
    vector<int> result;
    
    for(int i = nums.size()-1; i >= 0; i--) {
        if(nums[i] >= largest)
            result.emplace_back(nums[i]);
        largest = max(largest, nums[i]);
    }
    reverse(result.begin(), result.end());
    return result;
}

ostream& operator<<(ostream& out, vector<int> nums) {
    for(auto num: nums)
        out << num << " ";
    return out;
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
            
        cout << solve(nums) << endl;
    }
	return 0;
}