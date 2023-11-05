# https://leetcode.com/problems/the-number-of-employees-which-report-to-each-employee/

# Inner join to get the corresponding details for each employee with a valid managerId
# Then group by the managerId to get all the employees reporting and filter only if reportees >= 1
SELECT e2.employee_id, e2.name, COUNT(*) AS reports_count, ROUND(AVG(e1.age), 0) AS average_age
FROM Employees e1
JOIN Employees e2 ON e1.reports_to = e2.employee_id
GROUP BY e1.reports_to
HAVING COUNT(*) >= 1
ORDER BY employee_id
