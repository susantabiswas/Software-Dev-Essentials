# https://leetcode.com/problems/number-of-unique-subjects-taught-by-each-teacher/

# SOLUTION 1: Subquery
SELECT teacher_id, count(*) AS cnt
FROM (
    SELECT DISTINCT teacher_id, subject_id 
    FROM Teacher
) t
GROUP BY teacher_id

# SOLUTION 2
SELECT teacher_id, count(DISTINCT subject_id) AS cnt
FROM Teacher
GROUP BY teacher_id
