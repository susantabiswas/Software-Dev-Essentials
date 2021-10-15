# https://leetcode.com/problems/employees-earning-more-than-their-managers/

# Solution 1: Inner Join of the table with itself with manager ID and employee ID as JOIN criteria
SELECT E1.Name AS Employee
FROM Employee AS E1
JOIN Employee AS E2 ON E1.ManagerId = E2.Id
WHERE E1.Salary > E2. Salary;

# Solution 2: Inner Join of the table with itself using a sub query 
# with manager ID and employee ID as JOIN criteria
SELECT E1.Name AS Employee
FROM Employee AS E1
JOIN (SELECT * FROM Employee) E2 ON E1.ManagerId = E2.Id
WHERE E1.Salary > E2. Salary;
