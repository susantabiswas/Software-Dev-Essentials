/*
    https://leetcode.com/problems/find-median-from-data-stream/
    
    TC: O(logn)
    SC: O(n)
    n = no. of elements
    
    Median is a number which lies between a series of numbers. If there are
    even number of integers, then it is avg of middle two terms and if it is 
    odd then it is the middle element.
    Also, elements before the median are all smaller and elements after are all 
    bigger.
    So, we need to keep track of the largest of smaller number range and the smallest
    of large number range.
    For doing this we use two heaps, max-heap keeps track of the smaller range and
    min-heap keeps track of larger numbers.
    Since there can be odd number of terms, so we keep more terms in max-heap.
    Every time a new number comes in, we insert it in one of the heaps first, then
    check which heap has more terms.
    If both are of same size, then median is avg of two smaller and larger terms of each heap.
    If no. of terms are different then move elements from one heap to another to balance 
    the terms on both sides. Max-heap should have 1 more term than max-heap.

		TC: O(nlogn), n: no. of elements
		SC: O(n) for heap
*/
class MedianFinder {
    // Max heap tracks the elements on left of median
    // Max heap can have at most 1 extra element than the min heap when 
    // total no. of terms is odd
    priority_queue<int, vector<int>,less<>> max_heap;
    // Min heap tracks the elements on right of median 
    priority_queue<int, vector<int>, greater<>> min_heap;
public:
    MedianFinder() {
    }
    
    void addNum(int num) {
        if(max_heap.empty() || num <= max_heap.top())
            max_heap.emplace(num);
        else 
            min_heap.emplace(num);

        // check if rebalancing is needed or not
        if(max_heap.size() > min_heap.size() + 1) {
            min_heap.emplace(max_heap.top());
            max_heap.pop();
        }
        else if(max_heap.size() < min_heap.size()) {
            max_heap.emplace(min_heap.top());
            min_heap.pop();
        }
    }
    
    double findMedian() {
        // If both sides have the same size, means there are even no. of elements
        if(max_heap.size() == min_heap.size())
            return (double)(max_heap.top() + min_heap.top()) / 2;
        // Odd number of elements present
        return max_heap.top();
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
