/*
    https://leetcode.com/problems/domino-and-tromino-tiling/
    
    With the two types of tiles, there are total 6 types available with rotation.
    Out of those, 2 cannot be used as the last tile for filling. These are L rotated 90deg clockwise and
    L.
    So to keep the no. of ways unique, we make sure to fill the last position with an unique tile and repeat that.
    
    Nice explanation for the formula: https://leetcode.com/problems/domino-and-tromino-tiling/discuss/116581/Detail-and-explanation-of-O(n)-solution-why-dpn2*dn-1+dpn-3
*/
class Solution {
private:
    const long long MOD = pow(10, 9) + 7; 
public:
    int numTilings(int N) {
        // when there is nothing to cover, can be done in one way
        if(N == 0)
            return 1;
        // dp(i): no. of unique ways of arranging the tiles
        vector<int> dp(N+1, 0);      
        dp[0] = dp[1] = 1;
        if(N >= 2)
            dp[2] = 2;
        if(N >= 3)
            dp[3] = 5;
        
        for(int i = 4; i <= N; i++)
            dp[i] = ((2 * dp[i - 1]) % MOD + dp[i - 3]) % MOD;
        
        return dp[N];        
    }
};
