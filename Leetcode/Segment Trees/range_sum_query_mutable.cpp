/*
  Range Sum query.
  https://leetcode.com/problems/range-sum-query-mutable/submissions/
*/

class NumArray {
private:
    vector<int> tree;
    int N = 0;
public:
    void buildSegmentTree(int node, int start, int end, 
                         vector<int>& tree, vector<int>& nums) {
        // leaf node
        if(start == end) {
            tree[node] = nums[start];
            return;
        }
        
        int mid = start + (end - start)/2;
        buildSegmentTree(2*node + 1, start, mid, tree, nums);
        buildSegmentTree(2*node + 2, mid+1, end, tree, nums);
        
        tree[node] = tree[2*node + 1] + tree[2*node + 2];
    }
    
    NumArray(vector<int>& nums) {
        N = nums.size();
        if(N == 0)
            return;
        tree.resize(4 * N, 0);
        buildSegmentTree(0, 0, N-1, tree, nums);
    }
    
    void updateSegmentTree(int idx, int val, int node, int start,
                          int end, vector<int>& tree) {
        if(start == end) {
            tree[node] = val;
            return;
        }    
        
        int mid = start + (end - start)/2;
        
        if(start <= idx && idx <= mid) {
            updateSegmentTree(idx, val, 2*node + 1, start, mid, tree);
        }
        else {
            updateSegmentTree(idx, val, 2*node + 2, mid+1, end, tree);
        }
        
        tree[node] = tree[2*node + 1] + tree[2*node + 2];
    }
    
    void update(int i, int val) {
        if(N == 0)
            return;
        updateSegmentTree(i, val, 0, 0, N-1, tree); 
    }
    
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
    
    int sumRange(int i, int j) {
        if(N == 0)
            return 0;
        int val=rangeQuery(i, j, 0, 0, N-1, tree);
       
        return val;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */
