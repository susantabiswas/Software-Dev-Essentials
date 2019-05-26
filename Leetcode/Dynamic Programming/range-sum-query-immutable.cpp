/*
    303. Range Sum Query - Immutable
    https://leetcode.com/problems/range-sum-query-immutable/
    
    We use a vector to store the cummulative sum.
    For range[i:j]: sum[j] - sum[i], when i > 0
                    sum[j], when i == 0
*/

class NumArray {
private:
    vector<int> _sum_nums;
public:
    NumArray(vector<int>& nums) {
        if(nums.empty())
            return;
        
        _sum_nums.resize(nums.size(), 0);
        _sum_nums[0] = nums[0];
        // find the cummulative sum
        for(int i = 1; i < nums.size(); i++) {
            _sum_nums[i] += _sum_nums[i-1] + nums[i];
        }
    }
    
    int sumRange(int i, int j) {
        if(i == 0)
            return _sum_nums[j];
        else
            return _sum_nums[j] - _sum_nums[i-1];
     }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */
