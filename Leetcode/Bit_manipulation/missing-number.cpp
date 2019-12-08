/*
  https://leetcode.com/problems/missing-number/submissions/
*/

class Solution {
public:
    int missingNumber(vector<int>& arr) {
        // find the XOR values of all the array elements
        long long xor_arr = 0;
        for(const int& el: arr)
            xor_arr ^= el;
        
        long long xor_all = 0;
        // find the xor of [0:n]
        for(int i = 0; i <= arr.size(); i++ )
            xor_all ^= i;
        
        // if XOR of all the values from the array and [0:n] is taken, then each duplicate
        // term will cancel each other except for the single term missing
        return xor_arr ^ xor_all;
    }
};

    

