/*
    933. Number of Recent Calls
    https://leetcode.com/problems/number-of-recent-calls/
    
    Keep a queue to keep track of ping times, for each new ping
    we pop the queue elements if they are not in [t-3000, t]. Then 
    push the current time and return queue size.
    
    TC: O(n)
*/

class RecentCounter {
private:
    // keeps track of ping times
    queue<int> q;    
public:
    RecentCounter() {
        
    }
    
    int ping(int t) {
        // check if the oldest ping time is in [t-3000, t]
       while(!q.empty() && q.front() < (t - 3000))
           q.pop();
        q.emplace(t);
        
        return q.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
