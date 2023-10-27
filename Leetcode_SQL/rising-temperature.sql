# https://leetcode.com/problems/rising-temperature/

# Self Join with criteria of 1 day difference
SELECT today.id
FROM Weather as today, Weather as yesterday
WHERE DATE_ADD(yesterday.recordDate, INTERVAL 1 DAY) = today.recordDate
and today.temperature > yesterday.temperature;
