/*
    https://leetcode.com/problems/can-place-flowers/
    
    TC: O(N)
    SC: O(1)
    
    Idea is to simple iterate through to the elements and check
    if a position is suitable. Place the flower if the position is suitable 
    as we go.
*/
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        if(n > flowerbed.size())
            return false;
        
        for(int i = 0; i < flowerbed.size(); i++) {
            if(n == 0)
                return true;
            
            if(flowerbed[i] == 0) {
                bool possible = true;
                // check the previous position
                if(i-1 >= 0 && flowerbed[i-1])
                    possible = false;
                // check the next position
                if(i+1 < flowerbed.size() && flowerbed[i+1])
                    possible = false;
                
                if(possible) {
                    --n;   
                    flowerbed[i] = 1;
                }
                
            }
        }
        return n <= 0;
    }
};
