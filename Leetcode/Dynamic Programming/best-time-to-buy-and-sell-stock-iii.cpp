/*
    https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
    
    https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/478218/Simple-C%2B%2B-O(n)-solution.-Detailed-Explanation
    // Solution 1
    We use state transition for this. Since there are two transactions, that means there are 4 states:
    
    (Bought1)---sell---->(Sold1)-----buy----->(Bought2)------sell----->(Sold2)
    
    Also for each of the states, we can decide to not do anything, that would mean just using the
    current state.
    TC: O(N), SC: O(1)
    
    
    
    // Solution 2
    We keep track of the maximum profit that can be made if a stock is sold on ith day.
    This can be done by tracking the min stock price till i-th day by traversing from left.
    We store the above info, then we start traversing from right side keeping track of max price and max profit.
    Max right price till i-th day corresponds to share price at which any stock bought before
    before i-th day can be sold. Also track the max profit of doing the second transaction.
    
    So the day which gives the max combined profit for the above two will be the final answer.
    
    TC: O(N), SC:O(N)
*/
class Solution {
public:
    // Solution 1: Using state transitions
    int maxProfit(vector<int>& prices) {
        if(prices.empty())
            return 0;
        
        // All the variables below are in terms of profit we have 
        // Bought for the first time
        int bought1 = -1 * prices[0];
        // Sold for the first time
        int sold1 = 0;
        // Bought for the second time
        int bought2 = INT_MIN;
        // Sold for the second time
        int sold2 = 0;
        
        for(int i = 1; i < prices.size(); i++) {
            bought1 = max(bought1, -1 * prices[i]);
            sold1 = max(sold1, bought1 + prices[i]);
            bought2 = max(bought2, sold1 - prices[i]);
            sold2 = max(sold2, bought2 + prices[i]);
        }
        
        return sold2;
    }
    
    
    // Solution 2
    int maxProfit2(vector<int>& prices) {
        if(prices.empty())
            return 0;
        
        // i-th entry: max profit that can be made by selling stock that day
        vector<int> max_profit_today(prices.size(), 0);
        int min_stock_so_far = prices.front(), max_stock_after_this = prices.back();
        int max_profit = 0;
        // max profit that can be made by doing a transaction after current day
        int max_profit_after_this = 0;
        
        // find the profit that can be made by doing first transaction
        for(int i = 0; i < prices.size(); i++) {
            // this is updated first so that we there is no stock with lower, price
            // then profit stays 0 instead of selling at a loss
            min_stock_so_far = min(min_stock_so_far, prices[i]);
            max_profit_today[i] = prices[i] - min_stock_so_far;
        }
        
        // profit that can be made by doing the second transaction
        for(int i = prices.size() - 1; i >= 0; i--) {
            // update max stock on right
            max_stock_after_this = max(max_stock_after_this, prices[i]);
            // check if the current stock if bought and sold later can make the max profit for 2nd transaction
            max_profit_after_this = max(max_profit_after_this, 
                                        (max_stock_after_this - prices[i]));
            max_profit = max(max_profit,
                            max_profit_today[i] + max_profit_after_this);
        }
        
        return max_profit;
    }
};
