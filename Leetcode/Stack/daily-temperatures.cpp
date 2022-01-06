/*
    https://leetcode.com/problems/daily-temperatures/submissions/
    
    Solution 1
    This problem can be thought of as finding the closest greater temp for 
    each position. So we use a stack to keep track of temps from right in non-decreasing order,
    for the current day check if any of the temps afterwards were higher.
    
    TC: O(N)
    SC: O(N)
    
    Solution 2
    Idea is to use the answer computed for the elements on right. For ith day, we can start the
    search from i+1 day. First check if it is greater, if greater than asnwer = 1
    else if it is smaller, we use its warmer day info. we make our search day = current_day + answer[i+1],
    then repeat the process there.
    For element which dont have a warmer day, we keep track of hottest day from right.
    
    
    TC: O(2*N) ~ O(N)
        The inner loop in total for all the elements only traverses at most N elements. This is due to the
        fact that once an element at ith position has searched for the warmer day by visiting multiple 
        days after it, a day before ith day which is warmer than ith day need not do the same and 
        directly start from answer[i], skipping the days in between.
        
        So outer loop : O(N)
        Inner loop in total: O(N)
    SC: O(1)
*/

class Solution {
public:
    // Solution 1
    vector<int> stackSol(vector<int>& temperatures) {
        // Temp in non-decreasing order
        stack<int> increasing_temps;
        vector<int> answer(temperatures.size(), 0);
        
        for(int i = temperatures.size() - 1; i >= 0; i--) {
            // If temperature of days after 'i' is smaller than current
            // then doesnt make sense to track those temps, since current temp is
            // hotter and will be considered for days before 'i'
            while(!increasing_temps.empty() &&
                temperatures[i] >= temperatures[increasing_temps.top()])
                increasing_temps.pop();
            
            // check if the current temp is smaller than temps 
            // found afterwards 
            answer[i] = increasing_temps.empty() ? 0 : increasing_temps.top() - i;
            // add the current temp to the historical data
            increasing_temps.emplace(i);
        }
        
        return answer;
    }
    
    // Solution 2
    vector<int> constantSpaceSol(vector<int>& temps) {
        int hottest_day = temps.size() - 1;
        vector<int> answer(temps.size(), 0);
        
        for(int curr_temp = temps.size() - 1; curr_temp >= 0; curr_temp--) {
            // check if the current temp is hottest, then 
            // answer would be 0
            if(temps[curr_temp] >= temps[hottest_day]) {
                hottest_day = curr_temp;
            }
            else {
                // Current temp is not the highest, so there exists atleast a
                // day whose temp is higher, we start the search from left to right
                
                // Init candidate for warmer day is the very next
                int warmer_day = 1;
                // if the candidate day is colder, then we directly search the
                // day which is warmer for this colder day. We can skip all the values
                // in between since those will be smaller than the colder temp and hence
                // the current temp as well
                while(temps[curr_temp + warmer_day] <= temps[curr_temp]) {
                    warmer_day += answer[curr_temp + warmer_day];
                }
                answer[curr_temp] = warmer_day;
            }
        }
        
        return answer;
    }
    
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        // return stackSol(temperatures);
        return constantSpaceSol(temperatures);
    }
};
