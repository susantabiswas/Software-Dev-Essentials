/*
    https://leetcode.com/problems/rotate-array/
    
    Right shifting by k, means taking last k numbers and bringing them
    to front from left to right order. The numbers before those will appear
    as it as after the k numbers. 
    Now this simple fact that [1, 2, 3, 4] when reversed brings the back elements to front, but the 
    order is always reversed is important. 
    So if the entire array is reversed, the k elements will also come to front, but then the
    order will be reversed as well. So what if we consider two groups of elements and make them
    already reversed and then apply the reverse operation on the entire array. This will bring the 
    k elements to front and also reverse(already reversed numbers) = original order.
    
    Two groups will be :  A[0: N - k - 1] and A[N - k: N]
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        const int N = nums.size();
        // find the net shift req since rotating N element N times 
        // results leads to same position
        k = k % N;
        
        // reverse the array A[0: N - k - 1] and A[N - k: N]
        reverse(nums.begin(), nums.begin() + N - k);
        reverse(nums.begin() + N - k, nums.end());
        
        // reverse the entire array
        reverse(nums.begin(), nums.end());
    }
};
