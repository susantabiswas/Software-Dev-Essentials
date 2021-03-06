/*
    https://practice.geeksforgeeks.org/problems/sorting-elements-of-an-array-by-frequency/0
*/
#include <bits/stdc++.h>
using namespace std;

void solve(vector<int> &nums) {
    // find the frequency map of elements
    unordered_map<int, int> freq;
    for(int &num: nums)
        freq[num] += 1;
        
    // We use the frequency map as priority
    // for comparing
    sort(nums.begin(), nums.end(),
        [&freq](int &a, int &b)->bool{
            return freq[a] > freq[b] ||
                (freq[a] == freq[b] && a < b);
        }
    );
    
    for(auto &num: nums)
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