/*
    https://leetcode.com/problems/maximum-length-of-pair-chain/
    
    Sol1 : DP
    TC: O(nlogn + n^2) ~ O(n^2)
    SC: O(n)
    n = len of array
    
    Sort the pairs in increasing and then the problem is reduced to LIS problem.
    We can then use LIS on the array.
    
    Sol 2: Greedy
    TC: O(nlogn)
    SC: O(n)
    
    Sort the pairs by the 2nd number. The intuition is, in (a, b), (c, d)
    b decides what can come after it. So it makes sense to have the smallest possible
    b so that next element can be accomodated easily.
    
    Then we track the current pair, if we see that pairs[i][0] > curr[1], then it means
    we can increase the chain length.
    Note that if pairs[i][0] < curr[1], we dont include it in LIS, the reason this is
    correct is because if pairs[i][0] would have been placed before curr, then we we would
    have a larger 'b' since pairs[i][1] > curr[1] because we had sorted by the 2nd dimension.
    
*/
class Solution {
public:
    // SOLUTION 1: DP + Sorting
    int lisSolution(vector<vector<int>>& pairs) {
        // sort in increasing order of 1st number and 2nd when a tie
        sort(pairs.begin(), pairs.end());
        int max_len = pairs.empty() ? 0 : 1;
        
        int n = pairs.size();
        vector<int> dp(n, 1);
        
        // Now perform the classic LIS on pairs
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(pairs[j][1] < pairs[i][0]) {
                    dp[i] = max(dp[i], 1 + dp[j]); 
                }        
            }
            max_len = max(max_len, dp[i]);
        }
        
        return max_len;
    }
    
    // SOLUTION 2: Greedy
    int greedySol(vector<vector<int>>& pairs) {
        // sort by the 2nd element in increasing order
        sort(pairs.begin(), pairs.end(), [](vector<int>& a, vector<int>& b){
            return a[1] < b[1];
        });
        
        int len = pairs.empty() ? 0 : 1;
        vector<int> curr = pairs.empty() ? vector<int>{} : pairs[0];
        
        for(int i = 1; i < pairs.size(); i++) {
            // current pair can be appended to the existing LIS chain
            if(curr[1] < pairs[i][0]) {
                curr = pairs[i];
                ++len;
            }
        }
        return len;
    }
    
    int findLongestChain(vector<vector<int>>& pairs) {
        // return lisSolution(pairs);
        return greedySol(pairs);
    }
};
