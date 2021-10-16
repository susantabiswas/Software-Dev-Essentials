# https://leetcode.com/problems/duplicate-emails/submissions/

# Group by Email and filter by groups with count >1
SELECT Email
FROM Person
GROUP BY Email
HAVING COUNT(*) > 1;
