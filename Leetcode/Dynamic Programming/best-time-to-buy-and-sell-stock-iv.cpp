/*
    https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
    
    We use state transition for this. Since there are k transactions, that means there are 2k states:
    One state when we have bought something and another when we have sold something.
    (Bought1)---sell---->(Sold1)-----buy----->(Bought2)------sell----->(Sold2)-----buy----->(Boughtk)------sell----->(Soldk)
    
    Also for each of the states, we can decide to not do anything, that would mean just using the
    current state.
    TC: O(Nk), SC: O(k)
*/

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(prices.empty() || k == 0)
            return 0;
        
        const int N = prices.size();
        // to buy stock on ith day and sell on i+1th day takes N/2 transactions and repeating.
        // and need no order to decide when to buy or sell
        // So if k > N/2, then there is no need to decide when to buy or sell
        if(k >= N / 2) {
            int total_profit = 0;
            for(int i = 0; i < N-1; i++)
                if(prices[i] < prices[i+1])
                    total_profit += (prices[i+1] - prices[i]);
            
            return total_profit;
        }
        
        // states after buying and selling
        // bought(i): (i+1) state in the state transition, 
        // each (except first) happens after a sold state
        vector<int> bought(k, INT_MIN);
        // sold(i): (i+2) state in state transition, each sold
        // state happens after (i+1)th bought(bought[i] in array) state
        vector<int> sold(k, INT_MIN);
        
        for(int i = 0; i < N; i++) {
            // first Bought and sold states
            bought[0] = max(bought[0], -prices[i]);
            sold[0] = max(sold[0], bought[0] + prices[i]);
            
            // update the remaining states
            for(int j = 1; j < k; j++) {
                // For each Bought state, either don't do anything or buy the current stock
                bought[j] = max(bought[j], sold[j-1] - prices[i]);        
                // Either don't sell or sell the stock bought earlier
                sold[j] = max(sold[j], bought[j] + prices[i]);
            }
        }
        
        // final answer is the last sold state
        return sold.back();
    }
};
