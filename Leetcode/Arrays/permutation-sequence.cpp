/*
    https://leetcode.com/problems/permutation-sequence/
    
    The idea is that for each number, other numbers can be arranged in (n-1)! ways.
    So we start looking for the arrangement of first number whose range of pmt has the kth
    pmt. Then we go futher in all the pmts with the first number fixed. In the next stage, again,
    look for the pmt range where our kth index can lie. Repeat this process k no. of times.
    
    Nice explnanation:
    https://leetcode.com/problems/permutation-sequence/discuss/22507/%22Explain-like-I'm-five%22-Java-Solution-in-O(n)
    
    TC: O(n^2)
    SC: O(1)
*/
class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> nums(n, 0);
        vector<long long> factorial(n + 1, 1);
        string pmt;
        
        // fill the number array and factorial for nth term
        for(int i = 1; i <= n; i++) {
            nums[i-1] = i;
            factorial[i] = i * factorial[i - 1];
        }
        
        // since the numbers are from 1.... n and it is 0-based indexed,
        // we make k also zero based
        k = k - 1;
        
        for(int i = 1; i <= n; i++) {
            // find the index in which the permutation we
            // are looking for lies
            int idx = k / factorial[n - i];
            pmt += to_string(nums[idx]);
            // now in next iteration, we need to look in the pmt
            // of remaining numbers without the starting sequence nums[idx]
            nums.erase(nums.begin() + idx);
            // update k, so as to account for not considering the previous permutations
            // idx * factorial[n - i]: this many pmt were removed from consideration
            k = k - (idx * factorial[n - i]);
        }
        return pmt;
    }
};
