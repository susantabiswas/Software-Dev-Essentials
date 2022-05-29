/*
    https://leetcode.com/problems/peeking-iterator/
    
    We use a var to store the value which peek() is supposed to give.
    this means iterator is actually one step ahead of what where it should be.
    
    During init, we store the 1st value in nxt var, this can be used to peek().
    Now when next() is called, the curr value of nxt is returned and nxt is given
    value of next element using parent's next() method.
*/
/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *  public:
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

class PeekingIterator : public Iterator {
private:
    // stores the next element
    int nxt = -1;
    // indicates whether there is any element for nxt var
    bool end_reached = false;
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    // Initialize any member here.
	    // **DO NOT** save a copy of nums and manipulate it directly.
	    // You should only use the Iterator interface methods.
	    
        // Get the ptr to next element, Orig Iterator's Next is at pos 1[0-indexed]
        if(Iterator::hasNext())
            nxt = Iterator::next();
        else
            end_reached = true;
	}
	
    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
        return nxt;
	}
	
	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
        int curr = nxt;
        // update the value of nxt with next element if it exists
        if(Iterator::hasNext())
            nxt = Iterator::next();
        else
            end_reached = true;
        return curr;
	}
	
	bool hasNext() const {
	    return end_reached == false;
	}
};
