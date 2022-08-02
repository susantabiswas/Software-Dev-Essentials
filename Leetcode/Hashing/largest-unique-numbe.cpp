/*
    https://leetcode.com/problems/largest-unique-number/
    
    Simply find the freq of each unique number and then look for the 
    number which has 0 repeatition and also the largest.
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    int largestUniqueNumber(vector<int>& A) {
        unordered_map<int, int> freq;
        // compute the frequency of all the unique numbers
        for(const int &num: A)
            freq[num] += 1;
        
        int max_num = INT_MIN;
        // Find the largest number which has freq of 1
        for(auto it = freq.begin(); it != freq.end(); it++)
            if(it->second == 1 && it->first > max_num)
                max_num = it->first;
        return max_num == INT_MIN ? -1 : max_num;
    }
};
