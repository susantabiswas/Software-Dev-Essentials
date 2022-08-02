/*
    First Unique Number
    
    https://leetcode.com/problems/first-unique-number/
    
    The idea is to use a hash table for keeping track of elements
    which have been inserted in the Data sttructure. The hash table
    has the following structure: [key(num): iterator to the node containing num in linked list].
    
    Linked list is used which serves as a FIFO queue. The queue contains only the elements which are
    unique. The order of insertion of elements decides the position of elements in queue.
    
    When an element is inserted to the data structure, it is checked if occurred before or not,
    if this is a duplicate instance, the element is removed from the linked list using the
    iterator address from hash table, this can be done in O(1) because of Doubly linked list.
    Also the iterator addr in hash table is updated to point to null, so that we dont use
    the same iterator again to delete the node which has already been deleted. The key is kept in 
    the hash table to remind that the element has occurred before but no longer in unqiue
    since the iterator is not a valid node.
    In case a new element comes which is unique, its entry is made in hash table and it is inserted
    at the back side of linked list and the iterator of that node is saved as value for that key.
    
    showFirstUnique: O(1)
    add: O(1)
*/
class FirstUnique {
private:
    list<int> unique_queue_;
    unordered_map<int, list<int>::iterator> unique_;
public:
    // adds an element to the FirstUnique Data structure
    // by handling insertion of elements in hash table and linked list
    // TC: O(1)
    void addElement(int num) {
        // check if the element is unique or not
        auto it = unique_.find(num);
        // Element is not unique, remove it from hash table
        // and queue
        if(it != unique_.end()) {
            if(unique_[num] != unique_queue_.end())
                unique_queue_.erase(unique_[num]);
            // set the iterator addr as NULL to indicate that 
            // node has been deleted
            unique_[num] = unique_queue_.end();
        }
        // element is unique, add to hash table and unique queue
        // in the order of arrival
        else {
            // add to last of queue
            unique_queue_.emplace_back(num);
            // add to hash table the number and its
            // node addr in linked list queue
            unique_.emplace(num, next(unique_queue_.end(), -1));
        }    
    }
    
    FirstUnique(vector<int>& nums) {
        for(const int& num: nums) {
            addElement(num);
        }
    }
    
    int showFirstUnique() {
        if(unique_queue_.empty())
            return -1;
        else
            return unique_queue_.front();
    }
    
    void add(int value) {
        addElement(value);
    }
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */
