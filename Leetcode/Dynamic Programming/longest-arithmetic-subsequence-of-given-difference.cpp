/*
    https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/
    
    Sol1: 
    Similar to classic LIS problem, just here we add a check to ensure that the
    previous term has the required common difference. If the previous term has the common
    difference, just like LIS we check if adding the current term will make the AP sequence
    longer or not.
    
    Sol2
    We traverse the array sequentially and for each number, check if its previous term in the 
    AP sequence exists. If it does, then the length of AP with current as the last term is:
    len = length of AP before excluding current term + 1
    
    So we use a hash table to maintain the length of AP with it being the last term in the
    sequence.
*/
class Solution {
public:
    // SOLUTION: DP (TLE)
    // TC: O(n^2)
    // SC: O(n)
    int dpSol(vector<int>& arr, int difference) {
        int n = arr.size();
        
        // lis[i] = max length of AP sequence ending here with common_diff = difference
        vector<int> lis(n, 1);
        int max_len = arr.empty() ? 0 : 1;
        
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < i; j++) {
                int common_diff = arr[i] - arr[j];
                
                if(common_diff == difference) {
                    lis[i] = max(lis[i], 1 + lis[j]);
                }
            }    
            max_len = max(max_len, lis[i]);
        }
        return max_len;
    }
    
    // SOLUTION : Hashing
    // TC: O(n)
    // SC: O(n)
    int hashingSol(vector<int>& arr, int difference) {
        int n = arr.size();
        
        // lis[i] = max length of AP sequence ending with current term with common_diff = difference
        // for same numbers, one with longer LIS is picked
        unordered_map<int, int> lis;
        int max_len = arr.empty() ? 0 : 1;
        
        for(int i = 0; i < n; i++) {
            // length of AP before current term
            int before_ap_len = 0;
            
            // check if its previous term in AP exists or not
            if(lis.count(arr[i] - difference))
                before_ap_len = lis[arr[i] - difference];
            
            // Add the current term with the previous AP sequence
            lis[arr[i]] = 1 + before_ap_len;
            
            max_len = max(max_len, lis[arr[i]]);
        }
        return max_len;
    }
    
    int longestSubsequence(vector<int>& arr, int difference) {
        // return dpSol(arr, difference);
        return hashingSol(arr, difference);
    }
};
