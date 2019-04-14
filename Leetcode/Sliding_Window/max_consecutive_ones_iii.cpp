/*
    Find longest sequence of 1s with limited number of flips
    1004. Max Consecutive Ones III
    https://leetcode.com/problems/max-consecutive-ones-iii/
    
    We use two pointers to keep track of start and end of current window. We expand
    till all the flips have been used and another zero is encountered, then shrink the window
    till no. of zeros is under control. After that update the max length if applicable.
*/

class Solution {
public:
    int longestOnes(vector<int>& arr, int K) {
        int flips = K;
        int i = 0, j = 0;
        int max_len = 0;
        
        while(i < arr.size()) {
            // expansion
            if(arr[i++] == 0) {
                --flips;
            }
            // shrinkage
            while(flips < 0) {
                if(arr[j++] == 0)
                    ++flips;
            }
            
            // update max length
            if(max_len < (i-j)) {
               max_len = i - j;
            }
        }
        return max_len;
    }
};
