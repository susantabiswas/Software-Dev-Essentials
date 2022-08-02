/*
    https://leetcode.com/problems/insert-delete-getrandom-o1/
*/
class RandomizedSet {
private:
    // (element, idx in array)
    unordered_map<int, int> elements_;
    default_random_engine gen_;
    vector<int> all_nums_;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(elements_.count(val))
            return false;
        // The new element is added to the last of vector 
        elements_.emplace(val, all_nums_.size());
        all_nums_.emplace_back(val);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(elements_.count(val)) {
            // to make the removal from array in O(1),
            // we swap it with the last element
            swap(all_nums_[elements_[val]], all_nums_.back());
            // update the index of swapped element in hash table
            elements_[all_nums_[elements_[val]]] = elements_[val];
            elements_.erase(val);
            all_nums_.pop_back();
            return true;
        }
        return false;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int low = 0, high = elements_.size() - 1;
        int idx = uniform_int_distribution<int>{low, high}(gen_);
        return all_nums_[idx];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
