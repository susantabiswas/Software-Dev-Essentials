# https://leetcode.com/problems/average-selling-price/

# Left join the price data with the sale records
# This will create a table with corresponding units sold for each of the selling prices time range wise
# NOTE: Left join is used because we want to keep the rows from Prices which didnt see any sales as well
# Next just group by product_id and find the avg, use IFNULL to make the null values as 0 in output
SELECT product_id, 
    IFNULL(ROUND(SUM(selling_price) / SUM(units), 2), 0) AS average_price 
FROM (
    SELECT Prices.product_id, units * price AS selling_price, units
    FROM Prices
    LEFT JOIN UnitsSold ON Prices.product_id = UnitsSold.product_id
        AND purchase_date BETWEEN start_date AND end_date
) p
GROUP BY product_id;
