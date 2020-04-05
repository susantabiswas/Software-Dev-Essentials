/*
    https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
    
    TC: O(N), SC: O(1)
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.empty())
            return 0;
        // profit when we are holding a stock
        int with_stock = 0, with_stock_prev = -prices[0];
        // profit without holding a stock at the moment
        int without_stock = 0, without_stock_prev = 0;
        
        for(int i = 1; i < prices.size(); i++) {
            // when a stock is held
            // 1. retain the existing stock
            // 2. Buy a stock if dont have a stock in hand
            with_stock = max({with_stock_prev,
                             without_stock - prices[i]}); 
            // when stock is not held
            // 1. Dont buy a stock
            // 2. Sell the currently held stock
            without_stock = max(without_stock_prev,
                                with_stock_prev + prices[i]);
            
            // update the previous states
            with_stock_prev = with_stock;
            without_stock_prev = without_stock;
        }
        return without_stock;
    }
};
