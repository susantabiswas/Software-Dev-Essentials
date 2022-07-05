/*
    https://leetcode.com/problems/koko-eating-bananas/
    
    The idea is similar to Painter's partition problem. 
    We use binary search on the search space of eating rates K.
    For a given eating rate we check if it is possible to finish eating all the
    piles, if possible then we look for the smallest such K, otherwise we increase
    the Eating rate.
*/

class Solution {
public:
    // TC: O(N)
    // Checks if finishing all the piles is possible or not
    bool isFinishingPossible(vector<int>& piles, int& rate, int& H) {
        int hrs_req = 0;
        for(const int& pile: piles) {
            hrs_req += pile / rate + (pile % rate ? 1 : 0);
        }
        return hrs_req <= H;
    }
    
    // TC: O(Nlog(INT_MAX))
    int minEatingSpeed(vector<int>& piles, int H) {
        if(piles.empty())
            return 0;
        
        int low = 1, high = INT_MAX;
        
        while(low < high) {
            int eating_rate = low + (high - low) / 2;
            // check if all the piles can be finished with this speed or not
            bool piles_finished = isFinishingPossible(piles, eating_rate, H);
            
            if(piles_finished)
                high = eating_rate;
            else
                low = eating_rate + 1;
        }
        
        return low;
    }
};
