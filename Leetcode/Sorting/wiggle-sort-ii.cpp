/*
    https://leetcode.com/problems/wiggle-sort-ii/
*/
class Solution {
public:
    // TC: avg O(N)
    void wiggleSort(vector<int>& nums) {
        if(nums.size() <= 1)
            return;
        
        // find the median element
        const int N = nums.size();
        // since K in partition algo is 0-indexed, so for odd numbers if we want middle of floor(N/2), add 1
        const int median_idx = N % 2 != 0 ? N/2 + 1 : N/2;
        
        // place the elements greater than median at odd positions
        // place the elements smaller than median at even positions
        int median_val = kthLargestPartition(nums, median_idx);
        
        // After partitioning the array can be(not always) like this: smaller_median | equal_median | greater_median
        // Now with that, we need to place the greater numbers at all the odd positions and smaller ones
        // at even positions, the problem is with numbers equal to median, they need to be put apart from each other
        // So just like Dutch Flag problem, we use three pointers, one will be used for writing smaller and other for larger
        // than median elements. The third one will be for traversing the array.
        // We start traversing from left and index for writing larger starts from right, so in time we will start moving the
        // equal elements at even indices towards left for the larger odd positions and for equal elements
        // at odd positions will be moved to even positions towards right, making the qual separated.
        
        // writes the larger numbers at each odd position 
        int greater_odd = 1;
        // writes the smaller number at each even position
        int smaller_even =  N % 2 == 0 ? N - 2 : N - 1; 
        for(int i = 0; i < N;) {
            // smaller element at odd position or anything before currently processed
            // smaller writer index
            if(nums[i] < median_val && (i < smaller_even || (i % 2 != 0))) {
                swap(nums[smaller_even], nums[i]);
                smaller_even -= 2;
            }
            // greater value at even position or anything after currently processed
            // greater writer index
            else if(nums[i] > median_val && (i > greater_odd || (i % 2 == 0))) {
                swap(nums[greater_odd], nums[i]);
                greater_odd += 2;
            }
            else
                ++i;
        }
   }
    
   // Partition the array
    // TC: O(N), SC: O(1)
    template<typename Comparator>
    int partitionArray(vector<int>& arr, int pivot_idx, int l, int r, Comparator comp) {
        int pivot_val = arr[pivot_idx];
        // index where the elements will be written
        int write_idx = l;

        if(l <= r) {
            // swap the pivot with the last element
            swap(arr[pivot_idx], arr[r]);
            // place all smaller values on left and larger values on right
            for(int i = l; i < r; i++) {
                // Use the comparator to decide what kind of element should go to left
                if(comp(arr[i], pivot_val))
                    swap(arr[write_idx++], arr[i]);
            }
            // place the pivot at its correct position
            swap(arr[write_idx], arr[r]);
        }
        return write_idx;
    }

    // Using partitioning algorithm, k is 0 indexed
    // Avg TC: O(N)
    // Worst case TC: O(N^2)
    int kthLargestPartition(vector<int>& arr, int k) {
        // random number generator
        default_random_engine gen((random_device())());

        int l = 0, r = arr.size() - 1;
        while(l <= r) {
            // generate a random index in [l, r]
            int pivot_idx = uniform_int_distribution<int>{l, r}(gen);    
            // partition the array wrt pivot element
            int partition_idx = partitionArray(arr, pivot_idx, l, r, less<>());
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
};
