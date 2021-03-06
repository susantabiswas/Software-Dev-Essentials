/*
    https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/submissions/
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        // Find the max candy count
        int max_candies = *max_element(candies.begin(), candies.end());
        vector<bool> result(candies.size(), false);
        
        for(int i = 0; i < candies.size(); i++) {
            if(candies[i] + extraCandies >= max_candies)
                result[i] = true;
        }
        return result;
    }
};
