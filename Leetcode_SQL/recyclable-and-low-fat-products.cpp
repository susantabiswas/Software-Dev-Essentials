/*
    https://leetcode.com/problems/recyclable-and-low-fat-products/
*/
# Write your MySQL query statement below
SELECT product_id
FROM Products
WHERE low_fats = 'Y' and recyclable = 'Y';
