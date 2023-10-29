# https://leetcode.com/problems/average-time-of-process-per-machine/

# The inner most source will perform an inner join to create row with start and end time for each machine_id, process_id pair
# Then we can project the duration for each process in that same subquery
# the outer query will take the duration for each machine_id, process_id pair and do a groupby on the machine_id which
# will bring all the processes belonging to the same machine together and we can take the avg there and project.

SELECT machine_id, ROUND(avg(duration), 3) AS processing_time
    FROM (
        SELECT activity_start.machine_id, activity_start.process_id, activity_end.timestamp - activity_start.timestamp AS duration
        from Activity AS activity_start
        JOIN Activity AS activity_end ON 
            (activity_start.machine_id = activity_end.machine_id AND
            activity_start.process_id = activity_end.process_id AND
            activity_start.activity_type = 'start' AND
            activity_end.activity_type = 'end')
    ) temp1
    GROUP BY machine_id

