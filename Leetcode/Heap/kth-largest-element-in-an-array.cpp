class Solution {
public:
    // Partition the array
    // TC: O(N)
    template<typename Comp>
    int partitionArray(vector<int>& arr, int pivot_idx, int l, int r, Comp comp) {
        int pivot_val = arr[pivot_idx];
        int write_idx = l;
            
        if(l <= r) {
            // swap the pivot with the last element
            swap(arr[pivot_idx], arr[r]);
            // place all smaller values on left and larger values on right
            for(int i = l; i < r; i++) {
                if(comp(arr[i], pivot_val))
                    swap(arr[write_idx++], arr[i]);
            }
            // place the pivot at its correct position
            swap(arr[write_idx], arr[r]);
        }
        return write_idx;
    }
    
    // Using partitioning algorithm
    // Avg TC: O(N)
    // Worst case TC: O(N^2)
    int kthLargestPartition(vector<int>& arr, int k) {
        default_random_engine gen((random_device())());
        
        int l = 0, r = arr.size() - 1;
        while(l <= r) {
            // generate a random index in [l, r]
            int pivot_idx = uniform_int_distribution<int>{l, r}(gen);    
            // partition the array wrt pivot element
            int partition_idx = partitionArray(arr, pivot_idx, l, r, greater<>());
            // if the pivot is the kth element return
            if(partition_idx == k-1)
                return arr[partition_idx];
            // if pivot index is greater than k, go to left side of pivot
            else if(partition_idx < k)
                l = partition_idx + 1;
            // if pivot index is smaller than k, go to right side of pivot
            else
                r = partition_idx - 1;
        }
        return -1;
    }
    
    // Using Heap
    // TC: O(nlogk)
    int kthLargestHeap(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<>> min_heap;
        
        // traverse through the array, popping the smallest
        // element each time from the min-heap. After traversal
        // we will be left with k largest elements
        for(const int& el: nums) {
            min_heap.emplace(el);
            if(min_heap.size() > k)
                min_heap.pop();
        }
        
        // The min-heap has k largest elements, so heap top
        // will be the kth largest elements since others will be more than that
        int kth_largest = 0;
        while(!min_heap.empty()) {
            kth_largest = min_heap.top(), min_heap.pop();
            break;
        }            
        
        return kth_largest;
    }
    
    int findKthLargest(vector<int>& nums, int k) {
        //return kthLargestHeap(nums, k);
        return kthLargestPartition(nums, k);
    }
};
