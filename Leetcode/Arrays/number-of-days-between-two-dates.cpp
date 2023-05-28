/*
    https://leetcode.com/problems/number-of-days-between-two-dates/
    
    TC: O(date)
    SC: O(1)
*/
// Based on the georgian calender rules, leap year should be 
// divisible by 4 except if it is a century year like 1900, 2000 etc i.e divisible by 100
// it cannot be a leap year.
// But there is one other exception to the century rule, if the century year is divisible by 400
// then it is allowed to be a leap year.
/*
    Here are a few examples:

    2004 is divisible by 4 but not by 100, so it is a leap year.
    1900 is divisible by 4 and by 100, but not by 400, so it is not a leap year.
    2000 is divisible by 4, by 100, and also by 400, so it is a leap year.
*/
class Solution {
public:
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100) || year % 400 == 0;     
    }
    
    int daysInMonth(int month, int year) {
        if(month == 2)
            return isLeapYear(year) ? 29 : 28;
        else if(month == 1 || month == 3 || month == 5 ||
               month == 7 || month == 8 || month == 10 || month == 12)
            return 31;
        return 30;
    }
    
    int toDays(string date) {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int days = stoi(date.substr(8, 2));
        
        int total = days;
        for(int y = 1971; y < year; ++y) 
          total = total + (isLeapYear(y) ? 366 : 365);  
        
        for(int m = 1; m < month; m++) 
            total += daysInMonth(m, year);
        
        return total;
    }
    
    int daysBetweenDates(string date1, string date2) {
        return abs(toDays(date1) - toDays(date2));
    }
};
