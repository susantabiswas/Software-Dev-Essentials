# https://leetcode.com/problems/classes-more-than-5-students/

SELECT class
FROM courses
GROUP BY class
HAVING COUNT(DISTINCT student) >= 5; 


####### SOLUTION 2
# For the source, we use the group by output of Courses and then on that output we 
# filter the classes with student  count < 5
SELECT class
FROM ( 
    SELECT class, count(student) AS num
    FROM Courses
    GROUP BY class
) AS classes
WHERE classes.num >= 5;





