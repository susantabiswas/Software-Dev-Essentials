# https://leetcode.com/problems/delete-duplicate-emails/submissions/

# Solution 1
-- Delete all the IDs that doesn't match the smallest IDs
DELETE FROM Person
WHERE Id NOT IN
-- Select the min ID for each unique email ID
(SELECT *
 FROM (SELECT MIN(Id) AS Id
     FROM Person
     GROUP BY Email)
 AS p
);

# Solution 2
-- Delete all the Ids which are greater than the smallest
DELETE FROM Person
WHERE Id IN 
(
    SELECT * FROM
    -- Self Inner Join to find the Ids that are not the smallest
    (SELECT p1.Id AS Id
        FROM Person AS p1
        JOIN Person AS p2 ON p1.Email = p2.Email 
        AND
        p1.Id > p2.Id
    ) AS p
);
