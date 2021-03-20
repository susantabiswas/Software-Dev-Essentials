/*
    https://leetcode.com/problems/subarrays-with-k-different-integers/submissions/
    
    We use a different problem to solve this. We find the number of substrings with atmost
    K unique chars. 
    substrings with exactly k = atmost unique (K) - atmost unique (K-1)
    This diff only leaves the substrings with exactly k unique chars
*/
class Solution {
public:
    // Finds the substring with atmost K unique chars
    int atmostK(vector<int>& arr, int K) {
        int i = 0, j = 0, substrings = 0;
        unordered_map<int, int> freq;
        const int N = arr.size();
        
        while(i < N) {
            // Expand the window
            if(K >= 0) {
                ++freq[arr[i]];
                if(freq[arr[i]] == 1)
                    --K;
                ++i;
            }
            // make the window valid
            while(K < 0) {
                --freq[arr[j]];
                if(freq[arr[j]] == 0)
                    ++K;
                ++j;
            }
            // Each valid contiguous window seen so far, add current number 
            // For : 1,2,3, k=2
            // 1: [1] 
            // 2: [2], [1,2]
            // 3: [3], [2,3], [1,2,3]
            // Pattern: current number at ith, can be added to all the contiguous subarrays
            // till i-1th pos.
            // In general, no. of contiguous subarrays in N length array: N * (N+1) / 2
            // Since we are traversing incrementally hence we add each time: 1 + 2 + 3 ....+ N
            substrings += i - j + 1;
        }
        return substrings;
    }
    
    int subarraysWithKDistinct(vector<int>& arr, int K) {
        return atmostK(arr, K) - atmostK(arr, K-1);
    }
};
