/*
    https://leetcode.com/problems/design-hashset/submissions/
*/

class MyHashSet {
    vector<list<int>> hash_table;
public:
    /** Initialize your data structure here. */
    MyHashSet() {
        hash_table.resize(100001);
    }
    
    int hash_pos(int key) {
        return key % hash_table.size();
    }
    
    // Searches for a key in hash table adjacency list
    list<int>::iterator searchElement(int &pos, int &key) {
        list<int>::iterator it = hash_table[pos].begin();
        
        for(; it != hash_table[pos].end(); it++)
            if(*it == key) 
                break;
        return it;
    }
    
    void add(int key) {
        int pos = hash_pos(key);
        
        // check if the element exists
        auto it = searchElement(pos, key);
        // element doesn't exist, so add
        if(it == hash_table[pos].end())
            hash_table[pos].emplace_back(key);
    }
    
    void remove(int key) {
        int pos = hash_pos(key);
        
        // check if the element exists
        auto it = searchElement(pos, key);
        // element exists, remove it
        if(it != hash_table[pos].end())
            hash_table[pos].erase(it);
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        int pos = hash_pos(key);
        
        // check if the element exists
        auto it = searchElement(pos, key);
        // element exists
        if(it != hash_table[pos].end())
            return true;
        return false;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
