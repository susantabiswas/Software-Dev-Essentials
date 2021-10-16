# https://leetcode.com/problems/rising-temperature/submissions/

# Self Join with criteria of 1 day difference
SELECT w1.Id
FROM Weather w1, Weather w2
WHERE DATE_ADD(w2.RecordDate, INTERVAL 1 DAY) = w1.RecordDate
    AND w1.Temperature > w2.Temperature ;
