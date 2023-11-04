# https://leetcode.com/problems/user-activity-for-the-past-30-days-i/

# 1. Filter the source data by removing out of date range data and ones
# where there was no activity
# 2. Then just group by day timestamp and get count of unique users
SELECT activity_date AS day, COUNT(DISTINCT user_id) AS active_users
FROM Activity
WHERE activity_type IS NOT NULL
    AND activity_date BETWEEN DATE_SUB('2019-07-27', INTERVAL 29 DAY) AND DATE('2019-07-27')
GROUP BY activity_date
