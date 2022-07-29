/*
    https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
    
    TC: O(klogk)
    SC: O(k)
    
    Idea is very similar to the merging k sorted arrays. Since the rows and cols are
    sorted, we can treat the rows as sorted individual arrays.
    We use a min heap of size k, starting with the 1st element from each row.
    Popping the elements from heap k-1 times, pushing the next element of popped element if 
    that exists.
    
    In case two row values are same, we pick the next row value with higher column index, since
    elements increase column wise as well
*/
class Solution {
public:
    int kthSmallest(vector<vector<int>>& nums, int k) {
        int num_arrays = nums.size();
        
        using vector_it = vector<int>::const_iterator;

        // Custom comparator, uses the current running iterator's value to compare
        auto comp = [&](const tuple<vector_it, vector_it, int> it1, 
                        const tuple<vector_it, vector_it, int> it2) { 
            // If both have the same value, pick the column with higher index
            // as values as sorted column wise as well so the higher column might
            // have a bigger next value
            if(*(get<0>(it1)) == *(get<0>(it2)))
                return get<2>(it1) < get<2>(it2);
            return *(get<0>(it1)) > *(get<0>(it2)); 
        };
        // create a min heap that tracks num_arrays elements at a time
        // <iterator, iterator end, array index to which belongs>
        priority_queue<tuple<vector_it, vector_it, int>, 
            vector<tuple<vector_it, vector_it, int>>, decltype(comp)> 
        min_heap(comp);
        
        // Add the first element from each array
        for(int idx = 0; idx < num_arrays; idx++)
            if(!nums[idx].empty()) {
                min_heap.emplace(make_tuple(nums[idx].cbegin(), nums[idx].cend(), idx));
            }
        
        // Everytime pop the smallest element, if there is another element in the same array
        // that is pushed
        // Pop the elements k-1 times
        while(k-- > 1 && !min_heap.empty()) {
            auto [curr_it, end_it, arr_idx] = min_heap.top();
            min_heap.pop();
            
            // If next element exists, push to heap
            if(next(curr_it) != end_it)
                min_heap.emplace(make_tuple(next(curr_it), end_it, arr_idx));
        }
        // Get the kth element
        return *get<0>(min_heap.top());
    }
};
