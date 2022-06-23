/*
    https://leetcode.com/problems/logger-rate-limiter/
    
    Solution 1: Hash Table
    We use hash table to store the last printed message time for each of the unique messages. 
    TC: O(1)
    Cons: Memory exhaustion
    Pros: Simple to implement
    
    Solution 2: Two sets
    Idea is to keep two sets. Each set keeps track of one interval of 10s that is wrt to a start time.
    Set 1 keeps all the messages 10 seconds before start_time and set 2 keeps all the messages from start_time till 10s from there.
    For a given log, if the timestamp is in the curent interval, then check against that set.
    Else, the current set interval duration has elapsed and hence move the elements from that set
    to set1 because some elements might still have not completed 10s and hence we keep them safe in set1 for
    another 10s.
    
    Solution 3: Queue + Set
    
    Solution 4: Bucketing + Set
    
*/
// Solution 1: Hash Table
// Con: Memory can be overwhelmed with many unique logs as previous ones are
// not deleted
/*
class Logger {
private:
    unordered_map<string, int> last_printed;
public:
    Logger() {
    }
    
    bool shouldPrintMessage(int timestamp, string message) {
        // if the message is coming for the 1st time, print
        if(!last_printed.count(message)) {
            last_printed[message] = timestamp;
            return true;
        }
        else {
            int elapsed = timestamp - last_printed[message];
            if(elapsed >= 10)
                last_printed[message] = timestamp;
            return elapsed >= 10;
        }
    }
};
*/

// Solution 2: Two Sets
// Pros: Efficient use of memory.
class Logger {
private:
    // Indicates the start time of current interval of message requests
    int interval_start;
    int time_duration = 10;
    // Tracks messages in current interval of time_duration and
    // messages in previous time_duration interval
    // -10 prev_interval | interval_start | curr_interval +10
    
    // <message, timestamp>
    unordered_map<string, int> curr_interval, prev_interval;
public:
    Logger(): interval_start(0) {}
    
    bool shouldPrintMessage(int timestamp, string message) {
        // check if the current log can be put in the current interval 
        if(timestamp >= interval_start + time_duration) {
            // Since current timestamp > interval of curr message requests,
            // move the requests received in last 10s to prev_interval and
            // clear the current interval so that it can receive new messages 
            // We move the messages to prev interval because there might be messages that
            // have not completed 10s eg timestamp = 19 (start_interval=10), so we move them
            // to prev_interval where it will wait for another 10s before that is also cleared
            prev_interval = curr_interval;
            curr_interval.clear();
            interval_start = timestamp;
        }
        
        // Check if the same log message came or not in the current interval
        if(curr_interval.count(message))
            return false;
        // check if same log exists in the previous 10s interval, check if that message
        // has recency > last 10s
        if(prev_interval.count(message) && prev_interval[message] + 10 > timestamp)
            return false;
        
        // add the current message to the current interval
        curr_interval.emplace(message, timestamp);
        return true;
    }
};


/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
