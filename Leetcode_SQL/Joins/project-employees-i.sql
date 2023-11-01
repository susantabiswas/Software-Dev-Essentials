# https://leetcode.com/problems/project-employees-i/


# 1. Inner join to get the exp column for each of the employees
# 2. Group by the project id and find the avg
SELECT project_id, ROUND(avg(experience_years), 2) AS average_years
FROM Project
JOIN Employee ON Project.employee_id = Employee.employee_id
GROUP BY project_id;
