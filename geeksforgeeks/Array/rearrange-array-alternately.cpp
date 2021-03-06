/*
    https://practice.geeksforgeeks.org/problems/-rearrange-array-alternately/0/
    
    Idea is to encode information about the orig num and the new number at each pos
    using a single traversal. Then we remove the orig num info using another traversal.
    
    Num: orig + new_num % max_num* max_num
    max_num: any number > max element of array
    
    Orig: Num % max_num
    new_num: Num / max_num
    
    TC: O(N)
    SC: O(1)
*/
#include <bits/stdc++.h>
using namespace std;

void solve(vector<long>& nums) {
    int max_idx = nums.size() - 1, min_idx = 0;
    // Max number to ensure that the
    // modulus always gives the individual numbers back
    long long max_num = nums.back() + 1;
    
    // we encode each number with : old num + new num
    for(int i = 0; i < nums.size(); i++) {
        // even pos: max element
        if(i % 2 == 0) {
            nums[i] = nums[i] + (nums[max_idx--] % max_num) * max_num;
        }
        // odd pos: min element
        else {
            nums[i] = nums[i] + (nums[min_idx++] % max_num) * max_num;
        }
    }
    
    // save only the info about new number
    for(long &num: nums)
        num = num / max_num;
}

ostream& operator<<(ostream& out, vector<long>& arr) {
    for(auto &num: arr)
        out << num << " ";
    return out;
}

int main()
{
    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        vector<long> nums(n);
        
        for(int i = 0; i < n; i++)
            cin >> nums[i];
            
        solve(nums);
        cout << nums << endl;
    }
	return 0;
}