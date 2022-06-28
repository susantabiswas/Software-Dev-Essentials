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

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
