/*
    https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/
    
    TC: Merging + Sliding Window
        O(nlogk + n)
    SC: O(n)
    n = total no. of elements across the arrays
    k = no. of sorted arrays
    
    Problem boils down to finding the smallest window that contains at least one element from each array.
    But in order to find the window, we first have to have a sorted array with elements from all the arrays.
    
    1. Merging the k sorted arrays:
    Using min heap we can do better than normal O(nlogn)
    2. Then to find the smallest window, use sliding window. It takes another O(n)
*/
class Solution {
public:
    // Merges k sorted arrays
    vector<pair<int, int>> mergeArrays(vector<vector<int>>& nums) {
        int num_arrays = nums.size();
        
        using vector_it = vector<int>::const_iterator;

        // Custom comparator, uses the current running iterator's value to compare
        auto comp = [&](const tuple<vector_it, vector_it, int> it1, 
                        const tuple<vector_it, vector_it, int> it2) { 
            return *(get<0>(it1)) > *(get<0>(it2)); 
        };
        // create a min heap that tracks num_arrays elements at a time
        // <iterator, iterator end, array index to which belongs>
        priority_queue<tuple<vector_it, vector_it, int>, 
            vector<tuple<vector_it, vector_it, int>>, decltype(comp)> 
        min_heap(comp);
        
        int total_nums = 0;
        // Add the first element from each array
        for(int idx = 0; idx < num_arrays; idx++)
            if(!nums[idx].empty()) {
                min_heap.emplace(make_tuple(nums[idx].cbegin(), nums[idx].cend(), idx));
                total_nums += nums[idx].size();
            }
        
        // <value, array index>
        vector<pair<int, int> > merged(total_nums);
        int write = 0;
        
        // Everytime pop the smallest element, if there is another element in the same array
        // that is pushed
        while(!min_heap.empty()) {
            auto [curr_it, end_it, arr_idx] = min_heap.top();
            min_heap.pop();
            
            merged[write++] = make_pair(*curr_it, arr_idx);
            // If next element exists, push to heap
            if(next(curr_it) != end_it)
                min_heap.emplace(make_tuple(next(curr_it), end_it, arr_idx));
        }
        
        return merged;
    }
    
    // Find the smallest window that contains elements from each array
    vector<int> minWindow(int k, vector<pair<int, int>>& nums) {
        int start = 0, end = 0;
        // smallest
        int min_start = 0, min_end = INT_MAX;
        int n = nums.size();
        // Tracks the array indices in the current window
        unordered_map<int, int> indices;
        
        while(end < n) {
            int num = nums[end++].second;
            // attempt window expansion    
            ++indices[num];
            
            // Shrink the window if the window is valid
            while(indices.size() == k) {
                int window = nums[end - 1].first - nums[start].first;
                
                if(window < (min_end - min_start)) {
                    min_start = nums[start].first;
                    min_end = nums[end - 1].first;
                }
                // Update the frequency of index
                int num = nums[start++].second;
                if(--indices[num] == 0)
                    indices.erase(num);
            }
        }
        
        return vector<int>{min_start, min_end};
    }
    
    vector<int> smallestRange(vector<vector<int>>& nums) {
        // Merge the k sorted arrays
        vector<pair<int, int>> sorted = mergeArrays(nums);
        // Find the smallest window that contains atleast one element from each array
        return minWindow(nums.size(), sorted);
    }
};
