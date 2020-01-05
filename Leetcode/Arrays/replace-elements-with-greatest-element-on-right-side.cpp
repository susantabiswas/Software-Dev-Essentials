/*
    https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/submissions/
    
    Start traversing from 2nd last element, write the max element seen so far there and check if the current
    element is greater than max seen so far, if yes update that for next (i-1)th index
    
    TC: O(N)
*/
class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        const int N = arr.size();
        vector<int> result(N, -1);
        
        // initial value for max right will be last element
        int max_so_far = arr[arr.size() - 1];
        
        for(int i = arr.size() - 2; i >= 0; i--) {
            result[i] = max_so_far;
            // update max 
            max_so_far = max(max_so_far, arr[i]);
        }
        
        return result;
    }
};
