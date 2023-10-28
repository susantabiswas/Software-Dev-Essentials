# https://leetcode.com/problems/employees-whose-manager-left-the-company/

# Just filter out all the rows where the manager_id is null or manager_id doesnt exist
# in distinct employee_id list
SELECT employee_id
FROM Employees as e1
WHERE salary < 30000
    AND e1.manager_id IS NOT NULL 
    AND e1.manager_id NOT IN (
        SELECT DISTINCT e2.employee_id
        FROM Employees as e2
    )
ORDER BY employee_id;
