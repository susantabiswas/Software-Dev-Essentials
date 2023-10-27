# https://leetcode.com/problems/second-highest-salary/

# SOLUTION 1
# Get the 2nd salary in the Source using LIMIT and OFFSET. If there is 0 or 1 record
# in the source, outer SELECT will return NULL
SELECT
    (SELECT 
        DISTINCT salary AS SecondHighestSalary 
    FROM 
        Employee
    ORDER BY 
     salary DESC
    LIMIT 1
    OFFSET 1) AS SecondHighestSalary;


# SOLUTION 2
SELECT 
    IFNULL(
        (SELECT 
            DISTINCT salary AS SecondHighestSalary 
        FROM 
            Employee
        ORDER BY 
         salary DESC
        LIMIT 1
        OFFSET 1),
        NULL
    ) AS SecondHighestSalary;
    
