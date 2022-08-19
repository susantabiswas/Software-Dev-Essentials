/*
  https://leetcode.com/problems/stone-game/
*/

class Solution {
public:
    // Solution 1: Bottom up iterative DP
    int maxStonesIter(vector<int>& piles) {
         // if there is only one stones alex wins
        if(piles.size() == 1)
            return true;
        
        // each entry(i, j): Max value that alex can have in piles[i:j]
        vector<vector<int>> dp(piles.size(), vector<int>(piles.size(), 0));
        int total = accumulate(piles.begin(), piles.end(), 0);
        
        for(int l = 1; l <= piles.size(); l++) {
            for(int left = 0; left < piles.size() - l; left++) {
                int right = left + l;
                
                if(left == right)
                    dp[left][right] = piles[left];
                else {
                    /*
                        For each entry, we find Alex will try to pick the value maximizing his score and
                        the opponent will pick the value which returns Alex with least available score
                    */
                     int front_picked = piles[left] + 
                            min(left+2 < piles.size() ? dp[left+2][right] : 0,
                                left + 1 < piles.size() && right - 1 >= 0 ? dp[left+1][right-1] : 0);
                    
                    int back_picked = piles[right] +
                                    min(left+1 < piles.size() && right-1 >= 0 ? dp[left+1][right-1] : 0,
                                        right - 2 >= 0 ? dp[left][right-2] : 0);
                    dp[left][right] = max(front_picked, back_picked);
                }
            }    
        }
        
        int alex_val = dp[0][piles.size()-1];
        return dp[0][piles.size()-1] > (total - alex_val);
    }
    
    // Solution 2: Recursive
    int maxStonesRec(vector<vector<int> >& dp, vector<int>& piles, int i, int j) {
        // base case
        if(i > j)
            return 0;
        if(dp[i][j] == 0) {
            // Alex picks from front or back to maximize his value, 
            // while lee will try to minimize whatever is left for Alex to pick
            int front_picked = piles[i] + 
                            min(maxStonesRec(dp, piles, i+2, j), maxStonesRec(dp, piles, i+1, j-1));
            int back_picked = piles[j] + 
                            min(maxStonesRec(dp, piles, i+1, j-1), maxStonesRec(dp, piles, i, j-2));
            dp[i][j] = max(front_picked, back_picked);
        }
        return dp[i][j];
    }
    
    bool maxStonesRecDriver(vector<int>& piles) {
         // if there is only one stones alex wins
        if(piles.size() == 1)
            return true;
        
        // each entry(i, j): Max value that alex can have in piles[i:j]
        vector<vector<int>> dp(piles.size(), vector<int>(piles.size(), 0));
        
        // find the total sum, Alex wins only if the value of his stones
        // is more than what lee can gather
        int total = accumulate(piles.begin(), piles.end(), 0);
        
        int alex_val = maxStonesRec(dp, piles, 0, piles.size()-1);
        
        for(auto v:dp){for(auto a:v)cout<<a<<" ";cout<<endl;}
        return alex_val > (total - alex_val);
    }
    
    bool stoneGame(vector<int>& piles) {
       return maxStonesIter(piles);
        //return maxStonesRecDriver(piles);
    }
};
