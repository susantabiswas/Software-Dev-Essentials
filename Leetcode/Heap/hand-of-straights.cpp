/*
    https://leetcode.com/problems/hand-of-straights/
    
    TC: O(NlogM), N = Total elements, M = Unique Elements
    
    Since we are concerned with window of consecutive elements of 
    size groupSize, we need a way to get the elements in a consecutive manner.
    We use a min heap to keep track of elements along with their freq. 
    We process each window with elements from heap and check if the elements
    popped are consecutive or not. 
    If the current window can be filled with elements, we check for any of those
    elements with freq > 1, which can be used to fill the other windows. Keep repeating
    this untill all the elements are placed.
*/
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        // Can't create same sized windows
        if(hand.size() % groupSize)
            return false;
        
        unordered_map<int, int> freq;
        for(auto num: hand)
            ++freq[num];
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > min_heap;
        for(auto num: freq)
            min_heap.emplace(num);
        
        vector<pair<int, int>> window(groupSize);
        
        while(!min_heap.empty()) {
            // put elements in current window   
            // process the elements of window, check 
            // if they are consecutive 
            for(int pos = 0; pos < groupSize; pos++) {
                window[pos] = min_heap.top();
                min_heap.pop();
                if(pos - 1 >= 0 && window[pos].first - window[pos-1].first != 1)
                    return false;
            }
            
            // if there is any element with freq > 1, then that can be used
            // for other window
            for(int i = 0; i < window.size(); i++)
                if(window[i].second > 1) {
                    --window[i].second;
                    min_heap.emplace(window[i]);
                }
        }
        
        return true;
    }
};
