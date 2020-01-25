/*
    https://leetcode.com/problems/shuffle-an-array/
*/
class Solution {
private:
    // save the original array and current array
    vector<int> orig, curr;
public:
    // checks if the index is valid
    bool isValid(int& idx) {
        return idx >= 0 && idx < orig.size();    
    }
    
    Solution(vector<int>& nums) {
        for(const int& num: nums) {
            orig.emplace_back(num);
            curr.emplace_back(num);
        }
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return orig;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        // generate two random indices and swap the numbers
        default_random_engine gen((random_device())());
        int idx1 = uniform_int_distribution<int>{0, orig.size()-1}(gen);
        int idx2 = uniform_int_distribution<int>{0, orig.size()-1}(gen);
        // swap the number
        if(isValid(idx1) && isValid(idx2))
            swap(curr[idx1], curr[idx2]);
        return curr;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
