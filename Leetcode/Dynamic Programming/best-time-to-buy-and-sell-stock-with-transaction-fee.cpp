/*
    https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
    
    The idea is to know what is the value we can have if we hold a stock or we don't hold a stock.
    
*/
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        // cash if we don't hold any stock
        int cash_without_stock = 0;
        // cash if we hold a stock
        int cash_with_stock = -1 * prices[0];
        
        for(int i = 1; i < prices.size(); i++) {
            // Cash with holding a stock:
            // 1. Sell the previous stock today and buy the stock today
            // 2. No stock till yesterday and buy stock today
            // 3. keep holding the previous stock
            cash_with_stock = max({cash_with_stock + prices[i] - fee - prices[i], 
                                    cash_without_stock - prices[i],
                                    cash_with_stock
                                });
            // Cash without holding stock: 
            // 1. keep cash we had the previous day
            // 2. sell the stock we had till yesterday 
            cash_without_stock = max(cash_without_stock,
                                    cash_with_stock + prices[i] - fee);
            
        }
        return cash_without_stock;
    }
};
