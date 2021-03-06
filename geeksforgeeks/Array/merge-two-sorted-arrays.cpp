/*
    https://practice.geeksforgeeks.org/problems/merge-two-sorted-arrays/0/
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> solve(vector<int>& nums1,
                vector<int>& nums2) {
    const int M = nums1.size(), N = nums2.size();
    vector<int> result;
    
    int i = 0, j = 0;
    while(i < M && j < N) {
        if(nums1[i] < nums2[j]) {
            result.emplace_back(nums1[i++]);
        }
        else
            result.emplace_back(nums2[j++]);
    }
    while(i < M)
        result.emplace_back(nums1[i++]);
    while(j < N)
        result.emplace_back(nums2[j++]);
    return result;
}

ostream& operator<<(ostream &out, vector<int>& nums) {
    for(const int &num: nums)
        out << num << " ";
    return out;
}

int main()
{
    int t, m, n;
    cin >> t;
    while(t--) {
        cin >> m >> n;
        vector<int> nums1(m);
        vector<int> nums2(n);
        
        for(int i = 0; i < m; i++)
            cin >> nums1[i];
        for(int i = 0; i < n; i++)
            cin >> nums2[i];
        
        auto result = solve(nums1, nums2);
        cout << result << endl;
    }
	return 0;
}