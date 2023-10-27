# https://leetcode.com/problems/find-customer-referee/

# Either project rows with null referee_id or when referred not by 2
SELECT 
    name
FROM 
    Customer
WHERE referee_id IS NULL 
    OR referee_id <> 2;
