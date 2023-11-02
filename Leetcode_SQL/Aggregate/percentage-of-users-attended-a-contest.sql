# SOLUTION 1
SELECT contest_id, 
    ROUND(COUNT(DISTINCT user_id) / (SELECT COUNT(*) FROM Users) * 100, 2) AS percentage
FROM Register
GROUP BY contest_id
ORDER BY percentage DESC, contest_id ASC;

# SOLUTION 2
SELECT contest_id, 
    ROUND(COUNT(DISTINCT Register.user_id) / COUNT(DISTINCT Users.user_id) * 100, 2) AS percentage
FROM Register, Users
GROUP BY contest_id
ORDER BY percentage DESC, contest_id ASC;
