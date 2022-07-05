/*
    https://leetcode.com/problems/stock-price-fluctuation/
    
    Core idea is to maintain a ordered set for <timestamp, price> and <price, HashTable(timestamps)>
    1st one is used for mapping the timestamps with their prices.
    2nd one is used for keeping track of min and max values, we can't just use vars to keep track of min and max,
    since an update can remove a max or min price, and then we won't have the next min/max value and we would need 
    a complete O(t) traversal. So we maintain a map of <price, timestamps>.
    For each update operation, we update the value in records and then also in min_max.
    
    min_max tracks for each price all the timestamps that has that price. So for the current update operation search for the
    old_price key in the min_max and remove that timestamp from its hashtable. If it's hash table becomes empty,
    then remove the price key as well.
    
    Difference between solution 1 and solution 2 is that, in solution 2 we keep track of current min and max for each update 
    operation and use those vars to return the value for each minimum() and maximum() call.
*/
/*
///////////////////////// SOLUTION 1
class StockPrice {
private:
    // Tracks price for each timestamp
    // <timestamp, price>
    map<int, int> records;
    // < value, Set(timestamps)>
    // Tracks the timestamps for a particular value
    map<int, unordered_set<int> > min_max;
public:
    StockPrice() {
    }
    
    // TC: O(log(t) + log(p)), t = no. of timestamps, p = no. of unique price values
    // SC: O(1), One entry added for each update operation. In total it takes O(t + v) space
    void update(int timestamp, int price) {
        // if the timestamp is new and not a correction
        if(!records.count(timestamp)) {
            records[timestamp] = price;
            min_max[price].emplace(timestamp);
        }
        // if it is a correction
        else {
            // Previous price currently set for the timestamp
            int prev_price = records[timestamp];
            // For the previous price, remove the entry of this timestamp
            min_max[prev_price].erase(timestamp);
            // If the price has no other timestamps supporting it, remove it
            if(min_max[prev_price].empty())
                min_max.erase(prev_price);
            
            // update the new price value for timestamp and also update the min-max map
            records[timestamp] = price;
            min_max[price].emplace(timestamp);
        }
    }
    
    // TC: O(log(t)), t = no. of timestamps
    // SC: O(logt)
    int current() {
        return records.rbegin()->second;
    }
    
    // TC: O(log(p)), p = no. of unique price values
    // SC: O(logp)
    int maximum() {
        return min_max.rbegin()->first;
    }
    
    // TC: O(log(p)), p = no. of unique price values
    // SC: O(logp)    
    int minimum() {
        return min_max.begin()->first;
    }
};
*/

//////////////////////// SOLUTION 2 /////////////////
// Constant time operation for minimum() and maximum() price
class StockPrice {
private:
    // Tracks price for each timestamp
    // <timestamp, price>
    map<int, int> records;
    // < value, Set(timestamps)>
    // Tracks the timestamps for a particular value
    map<int, unordered_set<int> > min_max;
    // tracks max and min prices
    int max_price = INT_MIN, min_price = INT_MAX;
public:
    StockPrice() {
        
    }
    
    // TC: O(log(t) + log(p) + 2*log(p)), t = no. of timestamps, p = no. of unique price values
    // SC: O(1), One entry added for each update operation. In total it takes O(t + v) space
    void update(int timestamp, int price) {
        // if the timestamp is new and not a correction
        if(!records.count(timestamp)) {
            records[timestamp] = price;
            min_max[price].emplace(timestamp);
        }
        // if it is a correction
        else {
            // Previous price currently set for the timestamp
            int prev_price = records[timestamp];
            // For the previous price, remove the entry of this timestamp
            min_max[prev_price].erase(timestamp);
            // If the price has no other timestamps supporting it, remove it
            if(min_max[prev_price].empty())
                min_max.erase(prev_price);
            
            // update the new price value for timestamp and also update the min-max map
            records[timestamp] = price;
            min_max[price].emplace(timestamp);
        }
        // update the max and min prices
        max_price = min_max.rbegin()->first;
        min_price = min_max.begin()->first;
    }
    
    // TC: O(log(t)), t = no. of timestamps
    // SC: O(logt)
    int current() {
        return records.rbegin()->second;
    }
    
    // TC: O(1)
    // SC: O(1)
    int maximum() {
        return max_price;
    }
    
    // TC: O(1)
    // SC: O(1)
    int minimum() {
        return min_price;
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */
