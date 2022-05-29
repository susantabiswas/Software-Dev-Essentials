/*
    https://leetcode.com/problems/task-scheduler/
    
    TC: O(N) + O(NlogM), M = Unique tasks, N = total tasks
    SC: O(M)
    
    This problem can be solved using greedy approach. To make the time min,
    we need to position the tasks types with max freq as early as possible, as they decide 
    the boundary. We use heap to keep track of task freq. Since the tasks need to separated by n 
    time, a window will have n+1 tasks. We fill the window with the avail tasks, utilizing the heap
    to get the max freq tasks first. Conitnue doing this untill all the tasks are placed.
*/
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> freq;
        for(auto task: tasks)
            ++freq[task];
        
        // Store final freq of each task type
        priority_queue<int, vector<int>, less<int>> task_freq;
        for(auto [task, freq]: freq)
            task_freq.push(freq);
        
        // Each window will have a size of n + 1, since this ensures
        // the min gap between 1st elements of consecutive windows is n
        vector<int> window(n + 1, 0);
        int pos = 0;
        int time_req = 0;
        // Simulate the placement of tasks.
        // we would want to keep the max freq tasks
        // first in the current window
        while(!task_freq.empty()) {
            // place the tasks in current window
            for(pos = 0; pos < window.size() && !task_freq.empty(); pos++) {
                window[pos] = task_freq.top();
                task_freq.pop();
            }
            // Now that tasks of diff types have been placed
            // check if any task type has more such tasks to place
            for(int i = 0; i < pos; i++) {
                if(window[i] > 1)
                    task_freq.push(--window[i]);
            }
            // Check if there are still tasks left for next window,
            // if Yes, means we took n+1 time in current window
            time_req += task_freq.empty() ? pos : n + 1;
        }
        
        return time_req;
    }
};
