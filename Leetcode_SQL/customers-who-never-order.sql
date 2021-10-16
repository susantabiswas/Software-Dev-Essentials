# https://leetcode.com/problems/customers-who-never-order/

# Solution 1
SELECT Name AS Customers
FROM Customers
WHERE Id NOT IN (
    SELECT Customers.Id
    FROM Customers
    JOIN Orders ON Orders.CustomerId = Customers.Id
);

# Solution 2
SELECT Name AS Customers
FROM Customers
WHERE NOT EXISTS (
    SELECT CustomerId 
    FROM Orders 
    WHERE Orders.CustomerId = Customers.Id
);

# Solution 3
SELECT Name AS Customers
FROM Customers
WHERE Id NOT IN (SELECT Customers.Id
                FROM Orders
                WHERE Orders.CustomerId = Customers.Id);
