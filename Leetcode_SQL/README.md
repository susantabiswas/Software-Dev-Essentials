# SQL Notes

# Query Execution Order
The order of execution for clauses in a query is typically as follows:

1. **FROM clause**: This clause specifies the tables from which data will be retrieved.
2. **WHERE clause**: This clause filters the rows based on a specified condition.
3. **GROUP BY clause**: This clause groups rows based on a specified column or expression.
4. **HAVING clause**: This clause filters the grouped rows based on a condition.
5. **SELECT clause**: This clause selects the columns or expressions that will be returned in the result set.
6. **ORDER BY clause**: This clause sorts the result set based on a specified column or expression.
7. **LIMIT/OFFSET clause**: This clause limits the number of rows returned in the result set.


Sources
(1) What Is the Order of Execution of an SQL Query? - Designcise. https://www.designcise.com/web/tutorial/what-is-the-order-of-execution-of-an-sql-query.
(2) Order of Execution of SQL Clauses - Stack Abuse. https://stackabuse.com/order-of-execution-of-sql-clauses/.
(3) What are SQL Query execution steps with example? - Complex SQL Queries. https://www.complexsql.com/sql-statements/.
(4) SQL Order of Execution With Examples - datalemur.com. https://datalemur.com/sql-tutorial/query-order-of-execution.
(5) Order of Execution in SQL Explained - Essential SQL. https://www.essentialsql.com/order-of-execution-in-sql-explained/.
