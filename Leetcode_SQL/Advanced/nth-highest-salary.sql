# https://leetcode.com/problems/nth-highest-salary/

# SOLUTION 1
# Order the salaries in descending and return the next row of n-1 index
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
    DECLARE M INT;
    SET offsetIndex = N-1;
      RETURN (
        SELECT 
            DISTINCT salary
        FROM 
          Employee
        ORDER BY 
          salary DESC
        LIMIT offsetIndex, 1 # Selects the next row after Mth index (0- based indexing)
      );
END


# SOLUTION 2
# Order the salary in descending and limit 1 after offset n
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
    SET N = N - 1;
    
    RETURN (
        SELECT DISTINCT salary
        FROM Employee
        ORDER BY salary DESC
        LIMIT 1
        OFFSET N # Offset is n-1, so return the next index which is nth
    );
END

