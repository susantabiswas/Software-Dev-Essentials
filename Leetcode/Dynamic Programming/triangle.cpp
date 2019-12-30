/*
  https://leetcode.com/problems/triangle/
*/

class Solution {
public:
    /*
        We start from bottom and go up. So for level 'i' and position 'j'.
        We select the min value of jth and j+1th index in the next level for the 
        current level jth index. In the end we end up with a single top value 
    */
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.empty())
            return 0;
        // tracks path sum values of current level
        vector<int> curr;
        // tracks the path sum values till last level
        vector<int> prev = triangle.back();
        
        for(int i = triangle.size() - 2; i >= 0; i--) {
            for(int j = 0; j < triangle[i].size(); j++) {
                // select the min of the adjacent values
                curr.emplace_back(min(prev[j], prev[j+1]) + triangle[i][j]);
            }
            prev = move(curr);
        }
        return prev.front();
    }
};
