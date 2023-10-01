/*
    https://leetcode.com/problems/task-scheduler-ii/
    
    TC: O(N)
    SC: O(1)
    
    This is a simulation problem, where we just need to ensure that the current
    task is atleast 'space' distance apart from its own kind.
    Use a hash table to track the last position of each task type and find out
    the gap required to place each task type.
*/
class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        unordered_map<int, int> pos;

        long long curr = 0;

        for(auto task: tasks) {
            if(pos.count(task)) {
                // last seen position of current task type
                int last = pos[task];
                // Find the gap between the last position and current pos if the 
                // task was to be placed here
                int gap = curr - last - 1;
                // if the gap is not enough, then take required steps forward
                curr += gap >= space ? 0 : space - gap; 
            }
            pos[task] = curr;
            ++curr;
        }
        
        // curr - 1 represents the last positioned index in 0 based form
        return curr;
    }
};
