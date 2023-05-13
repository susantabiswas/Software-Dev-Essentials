/*
    https://leetcode.com/problems/find-the-original-array-of-prefix-xor/
    
    TC: O(N)
    SC: O(1)
    
    XOR is commutative and associative. Also XOR of same bits result in 0.
    Using all these facts, we can observe one thing, i.e for pref[i], if we
    know the numbers till i-1 in original array, then to find the ith original 
    number, we can just do XOR(original numbers) XOR pref[i] = orig[i].
    
    eg:
    Pref = [5, 2, 0]
    Orig: [5, 7, 3], 
    orig[1] = 5 ^ 2 = 7
    orig[2] = 5 ^ 7 ^ 0 = 3
*/
class Solution {
public:
    vector<int> findArray(vector<int>& pref) {
        int n = pref.size();
        vector<int> orig(n);
        int orig_prefix = pref[0];
        
        orig[0] = pref[0];
        
        for(int i = 1; i < n; i++) {
            orig[i] = orig_prefix ^ pref[i];
            orig_prefix ^= orig[i];
        }
        return orig;
    }
};
