/*
    https://leetcode.com/problems/last-stone-weight/
    
    Using max heap, we can get the haviest stones each time for smashing.
    Remove the stones and push the resultant of smashing in heap, do till 
    heap has 1 stone left.
    
    TC: O(nlogn)
*/
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        if(stones.empty())
            return 0;
        
        // create a max heap with stone weights
        priority_queue<int, vector<int>, less<>> max_heap(begin(stones), end(stones));
        
        while(max_heap.size() > 1) {
            int stone1 = max_heap.top();
            max_heap.pop();
            int stone2 = max_heap.top();
            max_heap.pop();
            
            // add the result of smash
            max_heap.emplace(stone1 - stone2);
        }
        return max_heap.top();
    }
};
