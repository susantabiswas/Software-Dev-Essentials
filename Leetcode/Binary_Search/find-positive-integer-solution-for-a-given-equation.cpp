/*
    https://leetcode.com/problems/find-positive-integer-solution-for-a-given-equation/submissions/
    
    TC: O(xy)
*/

/*
 * // This is the custom function interface.
 * // You should not implement it, or speculate about its implementation
 * class CustomFunction {
 * public:
 *     // Returns f(x, y) for any given positive integers x and y.
 *     // Note that f(x, y) is increasing with respect to both x and y.
 *     // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
 *     int f(int x, int y);
 * };
 */

class Solution {
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        int x = 1, y = 1000;
        vector<vector<int>> result;
        
        // We do grid search, where the rows = x and col = y
        for(; x <= 1000; x++) {
            while(customfunction.f(x,y) > z && y >= 1)
                --y;
            if(y >= 1 && customfunction.f(x,y) == z)
                result.emplace_back(vector<int>{x, y});
        }
        return result;
    }
};
