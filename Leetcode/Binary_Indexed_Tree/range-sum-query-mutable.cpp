/*
    https://leetcode.com/problems/range-sum-query-mutable/
    
    Binary Indexed Tree Solution
    
    Binary Indexed Tree is an n-ary tree that stores has a size equal to the size of input array
    unlike a segment tree where size is often 4n.
    
    1. Each node represents an index.
    2. Here the relationship between each node is based on the binary representation.
    A node x is child of node y, if on setting the rightmost set bit (LSB) makes it equal to y.
    Eg. x = 10110, y = 10100
    If we set the rightmost bit of x => 10100
    It becomes y.
    
    Similarly for x, 10111 can be a child.
    
    3. Each node index will account for values decided by its LSB. Eg 1010, LSB number is 10, so it will account for
    last 2 numbers in the array including itself. So bit[1010 (10)] = Accounts for nums[9:8], Bit has 1 based indexing
    hence 1010 accounts for 9-8 (0 based indexing).
    
    idx      Coverage
    (4) 0100     |   LSB = 100. This covers 4 nums: last 3 numbers and itself
    (3) 0011 |   |   LSB = 1. This covers 1 num: 1 number (itself)
    (2) 0010   | |   LSB = 10. This covers 2 nums: last 1 number and itself
    (1) 0001 | | |   LSB = 1. This covers 1 num: itself
    (0) 0000         Doesn't cover anything
    
    4. For updates, it goes to that index and adds the delta change compared to current value. Then the nodes (not descendents),
    which accounts for a cummulative value involving this index are also updated.
    To go to the next node index: 
        index = index + (index & -index), (index & -index) = Extracts the set LSB number
        Adds the LSB number to current index to go to the next number
        
        Keep going to the next index till we don't cross the max fenwick tree size.
        
    5. For queries, eg [4,7] (1 based), we need prefixSum(7) - prefixSum(3)
    For finding prefixSum(x), go to the index, add its value. Now that index will account for last LSB numbers, so
    go up to its parent to get next set of accounted numbers, repeat the process till we reach dummy root 0.
    
    eg: prefixSum(3) => 0011, add its value, LSB number is 1 So it accounts for 1 number
    So next number is: 0011 - 1 => 0010 (2)
    At 2 (0010), add its value, LSB number is 10, so it accounts for 2 numbers
    Next number: 0010 - 10 => 0000 (0), No set bit, so stop 
    
    The sum is returned
    
    TC:
        n = no. of elements
        NumArray = O(nlogn), Since we use update for each of the n elements

        for both update and query we traverse either upwards or downwards based on last set bit. 
        Worst case we traverse for the all the bits in the number. Max index number is 'n', so log2(n) no. of
        bits will be present for traversal.

        Update: O(log2n), Traverses downwards in tree
        Query: O(log2n), Traverses upwards in tree
    
    SC:O(n)
    
    
*/
class NumArray {
    // Stores Binary Indexed Tree and original array 
    vector<int> bit, nums;
    int n = 0;
public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        this->nums = nums;
        // The parent node in BIT is dummy, so +1 the size
        bit.resize(n + 1, 0);
        // Build BIT by doing update operation for each index with the value
        for(int idx = 0; idx < nums.size(); idx++)
            updateBIT(idx + 1, nums[idx]);
    }
    
    // Makes the updates to applicable nodes. Delta is the net change
    // needed for each node.
    void updateBIT(int index, int delta) {
        // Propagate the delta downwards till within the array
        while(index < bit.size()) {
            // notice how only delta is added at each node and not replaced
            bit[index] += delta;
            // Go to next node by adding the last set bit number
            // (index & -index): Number created by right most set bit
            index = index + (index & -index);
        }    
    }
    
    void update(int index, int val) {
        // BIT works on 1 based indexing, convert to 1 based index
        ++index;
        // Find the delta change for the index value, this is done by comapring
        // the value at the original nums array
        updateBIT(index, val - nums[index-1]);
        // Set the value in original array, this will be 
        // useful next time when a delta is calculated
        nums[index-1] = val;
    }
    
    // Finds the prefix sum in nums[0:idx-1]
    int prefixSum(int idx) {
        int sum = 0;
        // Go upwards towards the root
        while(idx > 0) {
            sum += bit[idx];
            idx = idx - (idx & -idx);
        }    
        return sum;
    }
    
    int sumRange(int left, int right) {
        // convert to 1 based index
        ++left, ++right;
        // nums[right-1:left-1] = nums[right-1:0] - nums[left-1:0]
        return prefixSum(right) - prefixSum(left-1);
    }
};

 //////////////////////////////////////// SEGMENT TREE /////////////////////////////////////

/*
  Range Sum query.
  https://leetcode.com/problems/range-sum-query-mutable/

    Segment tree is a complete binary tree with the leaf nodes storing the actual value of array for 
    which it is built. Each inner node just stores the overall value for that subtree.
    Root represents [0, n] range and each subtree approx divides the range by half.
    So left subtree: [0, n/2]
    Right subtree: [n/2 + 1, n]

    These nodes will also save the value for that range.
    Eg: root will contain the answer to query [0, n], left subtree will store for [0, n/2]
    and right subtree for [n/2 + 1, n].

    Since we want to store a complete binary tree for an n sized array, based on analysis 4*n is 
    sufficient size for the segment tree to store all the nodes.

    Build: 
    Tree is built recursively and takes O(n) time.
    n leaf nodes and n-1 inner nodes are created

    Update:
    Each time only one of the nodes is selected and hence it traverses in a single path towards the 
    left nodes. So max takes O(heigh of tree) = O(log2N)

    Query:
    This also at max goes till the leaf node and hence takes O(log2N)

    Space Complexity:
    O(4*n) ~ O(n)
  Ref:
  https://leetcode.com/articles/a-recursive-approach-to-segment-trees-range-sum-queries-lazy-propagation/#
*/
class NumArray {
    vector<int> tree;
    int n = 0;
public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n, 0);
        
        buildSegmentTree(0, 0, n-1, nums);
    }
    
    // Builds the Segment tree from an array
    void buildSegmentTree(int tree_idx, int low, int high, vector<int>& nums) {
        // Leaf node reached
        if(low == high) {
            tree[tree_idx] = nums[low];
            return;
        }
        int mid = low + (high - low) / 2;
        // Build left and right subtrees
        buildSegmentTree(2*tree_idx + 1, low, mid, nums);
        buildSegmentTree(2*tree_idx + 2, mid + 1, high, nums);
        
        // Update the value of current node based on subtrees
        tree[tree_idx] = merge(tree[2*tree_idx + 1], tree[2*tree_idx + 2]);
    }
    
    // Kind of operation expected in a query
    int merge(int val1, int val2) {
        return val1 + val2;
    }
    
    void update(int index, int val) {
        return updateSegmentTree(0, 0, n-1, index, val);
    }
    
    void updateSegmentTree(int tree_idx, int low, int high, int idx, int val) {
        if(low == high) {
            tree[tree_idx] = val;
            return;
        }
        
        int mid = low + (high - low) / 2;
        // if the index lies in the right subtree
        if(idx > mid)
            updateSegmentTree(2*tree_idx + 2, mid + 1, high, idx, val);
        // index lies on the left side
        else
            updateSegmentTree(2*tree_idx + 1, low, mid, idx, val);
        
        // Now update the value of root parent node
        tree[tree_idx] = merge(tree[2*tree_idx + 1], tree[2*tree_idx + 2]);
    }
    
    int sumRange(int left, int right) {
        return query(0, 0, n-1, left, right);
    }
    
    int query(int tree_idx, int low, int high, int left, int right) {
        // Out of bound range
        if(right < low || left > high)
            return 0;
        
        // If the current segment falls entirely in the range, return the value
        if(left <= low && high <= right)
            return tree[tree_idx];
        
        int mid = low + (high - low) / 2;
        // If the range entirely lies on the right side
        if(left > mid)
            return query(2*tree_idx + 2, mid + 1, high, left, right);
        // Range lies entirely on left
        else if(right <= mid)
            return query(2*tree_idx + 1, low, mid, left, right);
        
        // Range is spread across left and right, so recursively split the operation
        // |Low......left......|mid|....right....High|
        int left_query = query(2*tree_idx + 1, low, mid, left, right);
        int right_query = query(2*tree_idx + 2, mid+1, high, left, right);
        
        return merge(left_query, right_query);
    }

    /*
        NOTE: Simplified Query function, above is faster since it takes one more
        pruning step. In this one an invalid function will still execute but will return by
        the out of bound check. 

        int rangeQuery(int l, int r, int node, int start, int end, vector<int>& tree) {
       // when query range is out of given range
        if(r < start || l > end)
            return 0;
        // when current range lie inside query range
        else if(l <= start && end <= r)
            return tree[node];
        else {
            int mid = start + (end - start)/2;
            int left = rangeQuery(l, r, 2*node+1, start, mid, tree);
            int right = rangeQuery(l, r, 2*node+2, mid+1, end, tree);
            
            return left + right;
        }
            
    }
    */
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */
