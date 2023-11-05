# https://leetcode.com/problems/biggest-single-number/

# 1. For the source: Get the group id with only single member
# 2. From that source, pick the max
SELECT MAX(num) AS num
FROM (
    SELECT num AS num
    FROM MyNumbers
    GROUP BY num
    HAVING COUNT(*) = 1
) n;
