/*
    978. Longest Turbulent Subarray
    https://leetcode.com/problems/longest-turbulent-subarray/submissions/
    
    Find the longest sequence of increasing-decreasing or vice-versa numbers
    
    We expand the window till the current element doesnt violate the constraint, now
    since the constraint is broken because of current index, so move the window start to 
    current index for trying next window.
    We try two things: assuming that odd positions > even positions and vice-versa and
    find the max length.
    
*/

class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        if(arr.empty())
            return 0;
        
        int max_len = 1;
        int i = 0, j = 0;
        
        // case when odd position is greater than even
        while(i < arr.size() - 1) {
            ++i;
            // if current element violtates the constraint, then
            // current index will be the start for next window
            if((i % 2 == 0 && arr[i] >= arr[i-1]) ||
               (i % 2 != 0 && arr[i] <= arr[i-1]))
                j = i;
                
            max_len = max(max_len, i - j + 1);
        }
        
        // case when even position is greater than odd position
        i = 0, j = 0;
        while(i < arr.size() - 1) {
            ++i;
            // if current element violtates the constraint, then
            // current index will be the start for next window
            if((i % 2 == 0 && arr[i] <= arr[i-1]) ||
               (i % 2 != 0 && arr[i] >= arr[i-1]))
                j = i;
                
            max_len = max(max_len, i - j + 1);
        }
        
        return max_len;
    }
};

//////////////////////////// Style 2
class Solution {
public:
    template<typename F1, typename F2>
    int maxTurbulentWindow(vector<int>& arr, F1 comp1,
                          F2 comp2) {
        int max_len = arr.empty() ? 0 : 1;
        int end = 0, start = 0;
        
        while(end < arr.size() - 1) {
            ++end;
            
            if((end % 2 == 0 && comp1(arr[end], arr[end-1])) ||
               (end % 2 != 0 && comp2(arr[end], arr[end-1])))
                start = end;
            
            max_len = max(max_len, end - start + 1);
        }
        return max_len;
    }
    
    int maxTurbulenceSize(vector<int>& arr) {
        if(arr.empty())
            return 0;
        
        int max_len = 0;
        auto less_than_equal = [&](const int& a, const int& b) { return a <= b; };
        auto greater_than_equal = [&](const int& a, const int& b) { return a >= b; };
        
        max_len = max(max_len, maxTurbulentWindow(arr, greater_than_equal, less_than_equal));
        max_len = max(max_len, maxTurbulentWindow(arr, less_than_equal, greater_than_equal));
        
        return max_len;
    }
};
