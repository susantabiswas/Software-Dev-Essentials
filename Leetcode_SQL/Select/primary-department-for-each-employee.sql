# https://leetcode.com/problems/primary-department-for-each-employee/

# SOLUTION 1: 
# Just Union(Employee row with a primary flag = Y,
# Employee with just one instance)
SELECT 
    employee_id, department_id
FROM Employee
WHERE 
    primary_flag = 'Y'
UNION
SELECT 
    employee_id, department_id
FROM Employee
GROUP BY 
    employee_id
HAVING 
    COUNT(*) = 1
    
# SOLUTION 2:
# Idea is to add a new column for each of the rows of employee table,
# this column is the count of all of the dept each employee belongs to.
# Now only the rows where department count = 1 OR primary_flag = Y are picked
SELECT employee_id, department_id
FROM (
    SELECT 
        *,
        COUNT(department_id) OVER(PARTITION BY employee_id) AS dept_count
    FROM Employee
) e
WHERE primary_flag = 'Y' OR dept_count = 1;
