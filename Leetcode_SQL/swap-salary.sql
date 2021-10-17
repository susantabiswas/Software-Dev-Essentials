# https://leetcode.com/problems/swap-salary/submissions/
-- Use If Else to set value

UPDATE Salary
SET 
    sex = 
    CASE
        WHEN sex = 'f' THEN 'm'
        WHEN sex = 'm' THEN 'f'
    END;
