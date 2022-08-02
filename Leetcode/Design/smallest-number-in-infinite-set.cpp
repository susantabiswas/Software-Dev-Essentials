/*
    https://leetcode.com/problems/smallest-number-in-infinite-set/
    
    To summarize the scenarios that can happen:
    Let x be the current smallest on the number line. This moves incrementally(+1) in forward direction always. 
    1. A number > x can't be added, since it is already present
    2. A number > x can't be removed
    3. A number = x can't be added
    4. A number = x can be removed during the popSmallest() call
    5. A number < x can only be added and that too once if it hasn't been popped yet
    6. Any past number added will always be smaller than x
    
    So looking at this, we don't need to worry about the future numbers, just deal with the past 
    numbers. Also by #6, it is clear any past number will be smaller than x and that will be popped first.
    
    So we need to track the past numbers that are added. For that we can use a min heap to track the smallest
    in O(1) and also use a hash table that tracks which numbers are added. Hash table is needed to prevent a duplicate
    entry into the heap.
    
    for every popSmallest, first return a number from the heap if available otherwise return x
*/
class SmallestInfiniteSet {
private:
// Keeps track of numbers that lie before the current smallest in the set. These
// numbers were popped once and now been added again
// We use a min heap to track the smallest added number in O(1)
priority_queue<int, vector<int>, greater<>> nums_before_curr;
// Keeps track of numbers added
unordered_set<int> added;
// Tracks the smallest number in the range ignoring the popped numbers added later again
int smallest = 1;
    
public:
    
    SmallestInfiniteSet() {
    }
    
    // TC: O(1)
    // SC: O(n), n = numbers added which haven't been popped
    int popSmallest() {
        // First check if a number was added that is smaller than the current smallest
        if(!nums_before_curr.empty() && nums_before_curr.top() < smallest) {
            int smallest_before_curr = nums_before_curr.top();
            // remove the number both from the hash table and min heap
            nums_before_curr.pop();
            added.erase(smallest_before_curr);
            
            return smallest_before_curr;
        }
        // If no numbers were added before the current smallest on number line
        return smallest++;
    }
    
    // TC: O(logn)
    // SC: O(n), n = numbers added which haven't been popped
    void addBack(int num) {
        // Only add the number if that has already been popped and not added again
        if(smallest > num && !added.count(num)) {
            nums_before_curr.emplace(num);
            added.emplace(num);
        }
    }
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */
