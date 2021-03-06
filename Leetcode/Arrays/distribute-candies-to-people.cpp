```
/*
    https://leetcode.com/problems/distribute-candies-to-people/submissions/
	
	Simple simulation.
	TC:  Each time the given candies increases by 1, so 1 + 2 + ..... + n = candies
	n*(n+1)/2 = candies
	~n^2 = candies
	~n = candies^0.5
	TC: O(sqrt(candies))
	
*/
class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> result(num_people, 0);
        int idx = 0, iteration = 0;
        
        while(candies > 0) {
            int candies_to_give = num_people * iteration + (idx + 1);
            result[idx] += min(candies_to_give, candies);
            candies -= candies_to_give;
            idx = (idx + 1) % num_people;    
            if(idx == 0)
                ++iteration;
        }
        
        return result;
    }
};
```
