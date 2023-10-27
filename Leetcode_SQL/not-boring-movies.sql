# https://leetcode.com/problems/not-boring-movies/submissions/

SELECT *
FROM Cinema
WHERE id % 2 <> 0 AND description <> 'boring'
ORDER BY rating DESC;


//////////// SOLUTION 2
SELECT *
FROM Cinema
WHERE id % 2 = 1 and description != 'boring'
ORDER BY rating DESC;
