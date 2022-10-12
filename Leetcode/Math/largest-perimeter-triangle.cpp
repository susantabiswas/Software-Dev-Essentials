/*
    https://leetcode.com/problems/largest-perimeter-triangle/
    
    TC: O(nlogn)
    SC: O(n)
*/
class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<>());
        
        // a + b > c, the two smaller sides should collectively be 
        // larger than the largest side. To get this combination, we need
        // to look for the 3 consecutive ones only. If i, i + 1 and i + 2 make
        // a valid triangle and i, i + 2 and i + 3 also makes a valid triangle then
        // perimeter is largest for the earliest combination.
        for(int i = 2; i < nums.size(); i++) {
            if(nums[i-2] < nums[i-1] + nums[i])
                return nums[i-2] + nums[i-1] + nums[i];
        }
        return 0;
    }
};
