# https://leetcode.com/problems/customer-who-visited-but-did-not-make-any-transactions/

#### SOLUTION 1
# Select all the records except for the ones whose 
# visit_id has an intersection (inner join) with Transactions table
# After the filtering, group the output by customer_id

SELECT customer_id, count(*) AS count_no_trans
FROM Visits AS v1
WHERE v1.visit_id NOT IN (
    SELECT v2.visit_id
    FROM Visits AS v2
    JOIN Transactions ON v2.visit_id = Transactions.visit_id
)
GROUP BY customer_id;


#### SOLUTION 2: Optimized: Inner join not needed, just dont pick the
# visit_id present in transactions table
SELECT customer_id, count(*) AS count_no_trans
FROM Visits
WHERE visit_id NOT IN (
    SELECT visit_id 
    FROM Transactions
)
GROUP BY customer_id;

