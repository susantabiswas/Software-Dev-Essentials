# https://leetcode.com/problems/combine-two-tables/submissions/

# Write your MySQL query statement below
SELECT FirstName, LastName, City, State
FROM Person
LEFT JOIN Address ON Address.PersonID = Person.PersonId
