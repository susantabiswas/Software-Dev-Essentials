# https://leetcode.com/problems/invalid-tweets/

SELECT tweet_id
FROM Tweets
WHERE CHAR_LENGTH(content) > 15;
