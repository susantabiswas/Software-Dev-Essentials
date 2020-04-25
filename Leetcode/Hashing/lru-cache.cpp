/*
	https://leetcode.com/problems/lru-cache/
	
    We use a hash table for storing a mapping between each key and its position in queue.
    A linked list implementation of queue is used for ordering the elements based on their 
    activity. Whenever an element is accessed it is moved to front of hash table to indicate 
    it was recently used. 
    When the cache is full, the last element of queue which is the LRU element is removed and
    its entry is removed from hahs table also.
    
    TC: get: O(1)
        put: O(1)
*/
class LRUCache {
private:
    int capacity_ = 0;
    // used for tracking recently used keys, front key
    // will the most recently used and last will be the least recently usde
    list<int> lru_queue;
    // key: (node addr, key)
    unordered_map<int, pair<list<int>::iterator, int>> lru_cache;
    
public:
    LRUCache(int capacity) {
        capacity_ = capacity;    
    }
    
    void moveToFront(unordered_map<int, pair<list<int>::iterator, int>> :: iterator it) {
        // remove the key from queue
        lru_queue.erase(it->second.first);
        // insert a new node at front for the key
        lru_queue.emplace_front(it->first);
        // update the ptr addr of node for the current key
        it->second.first = lru_queue.begin();
    }
    
    int get(int key) {
        // check if the key is in LRU cache 
        auto it = lru_cache.find(key);
        // key found
        if(it != lru_cache.end()) {
            // update the position of key in LRU queue,
            // bring it to front
            moveToFront(it);
            return lru_cache[key].second;
        }
        // key not found
        else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        auto it = lru_cache.find(key);
        // key is present, update the value and bring to front
        if(it != lru_cache.end()) {
            it->second.second = value;
            moveToFront(it);
        }
        // key is absent, insert it
        else {
            // remove the LRU key from cache and queue if capacity is reached
            // and insert the current key to front in queue 
            if(lru_cache.size() >= capacity_) {
                // remove the LRU entry
                auto lru_el = lru_queue.back();
                lru_queue.erase(lru_cache[lru_el].first);
                lru_cache.erase(lru_el);
            }
            // add the key in queue
            lru_queue.emplace_front(key);
            auto queue_addr = lru_queue.begin();
            // insert the entry in hash table for the given key
            lru_cache[key] = make_pair(queue_addr, value);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
