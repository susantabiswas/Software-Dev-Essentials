# https://leetcode.com/problems/replace-employee-id-with-the-unique-identifier/

SELECT EmployeeUNI.unique_id, name
FROM Employees
LEFT JOIN EmployeeUNI ON Employees.id = EmployeeUNI.id;
