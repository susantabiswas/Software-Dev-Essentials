/*
    https://leetcode.com/problems/time-based-key-value-store/
    
    set: TC: O(logm), SC: O(m), m = no. of timestamps 
    get(): TC: O(logm), SC: O(1)
    
    Idea is to keep the following the data structure:
    { key: {timestamp: value} }
    All the values for a key are kept together in a set (height balanced tree), so that
    they are ordered according to timestamp.
    Whenever we want to retrieve a timestamp value, we do binary search on the values stored
    in the records[key]. In case the exact timestamp is not present, return the 1st previous timestamp provided that is also present.
*/
class TimeMap {
private:
    // <key, {timestamp: value}>
    // Tracks the value for each of the keys timestamp wise
    unordered_map<string, map<int, string> > records;
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        records[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        // check if the key exists
        if(records.count(key)) {
            // Find the value closest to the given timestamp
            auto it = records[key].lower_bound(timestamp);
            // if the iterator is not equal to the given timestamp, then return the previous value
            // Also the previous timestamp value is only possible if there is a record of an earlier timestamp
            return it != records[key].end() && it->first == timestamp ? it->second 
                : (it == records[key].begin() ? "" : (--it)->second);
        }
        return "";
    }
};


/////////////////////////////// SOLUTION 2 : Different Style
class TimeMap {
private:
    unordered_map<string, map<int, string>> kv;
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        kv[key].insert({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        if(kv.count(key) == 0)
            return "";
        
        auto it = kv[key].lower_bound(timestamp);
        
        // key found
        if(it->first == timestamp)
            return it->second;
        
        // if key is not found, check if there is a key with TS < timestamp
        // but it cannot be the 1st element because, lower_bound gives the next greater in case of missing key
        //, so if it is the beginning iterator that means no smaller timestamp exists
        if(it == kv[key].begin())
            return "";
        // now there is atleast one timestamp that exists before the input 'timestamp', return the prev
        return (--it)->second;
    }
};


/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
