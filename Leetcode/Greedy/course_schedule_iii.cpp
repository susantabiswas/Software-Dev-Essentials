/*
    630. Course Schedule III
    https://leetcode.com/problems/course-schedule-iii/
    
    Sort the courses by deadlines.
    We start by looking at only those courses where deadline is more than the
    duration. Then we keep track of our total duration till current course, if current
    course's deadline crosses our duration, then we check if current course duration is lesser
    than any of the courses that we have considered, because there is no point in keeping
    a longer duration course when a shorter course with farther deadline is available.
    
    We use heap for keeping track of courses.
*/
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        // sort by deadlines
        sort(courses.begin(), courses.end(), [](const vector<int>&a, const vector<int>& b)->bool{
            return a.back() < b.back();
        });
        
        // heap for keeping track of largest duration course
        priority_queue<int, vector<int>, function<bool(int, int)> >
            pq([](const int&a, const int& b)->bool{
                return a < b;
                });
        
        // keeps track of total duration of considered courses
        int day = 0;
        int n = 0;
        
        for(int i = 0; i < courses.size(); i++) {
            // consider only valid courses
            if(courses[i].front() <= courses[i].back()){
                // check if current course can be taken or not
                // by looking at the deadline of current course if it is 
                // taken
                if(courses[i].back() >= (day + courses[i].front())) {
                    ++n;
                    day += courses[i].front();  
                    pq.emplace(courses[i].front());
                }
                
                // when current course's deadline crosses our duration, 
                // then check if any course can be replaced which has a longer duration 
                // with current course, this in turn will reduce the total duration and
                // we want to have lowest duration in order to accomodate more courses.
                else {  
                    int largest = pq.top();
                    if(largest > courses[i].front()) {
                        pq.pop();
                        pq.emplace(courses[i].front());
                        day = day - largest + courses[i].front();
                    }
                }
            }
        }
        return n;
    }
};
