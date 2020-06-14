/*
    https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/submissions/
    
    Idea is to remove the elements which appear the least number of times first, so that 
    unique elements decrease in number.
    
    SOLUTION 1: Using heap
    SOLUTION 2: Using sorting
    m: no. of unqiue elements, n: total elements
*/
class Solution {
public:
    // SOLUTION 1
    // TC: O(n) + O(m) + O(klogm): When using sorting
    // m: no. of unqiue elements, n: total elements
    int heapSol(vector<int>& arr, int k) {
        unordered_map<int, int> freq;
        for(const int num: arr)
            ++freq[num];
        
        // create an array of (freq, element)
        vector<int> element_freq;
        for(auto it = freq.begin(); it != freq.end(); it++)
            element_freq.emplace_back(it->second);
        
        // min heap with frequencies of each unqiue element
        priority_queue<int, vector<int>, greater<>> min_heap(element_freq.begin(), element_freq.end());
        
        // check the number of unique elements that remains after
        // greedily removing the lowest freq elements
        int unique = element_freq.size();
        while(!min_heap.empty()) {
            int curr = min_heap.top();
            min_heap.pop();
            if(curr > k)
                break;
            k = k - curr;
            --unique;
        }
        
        return unique;    
    }
    
    // SOLUTION 2
    // TC: O(n) +  O(mlogm): When using sorting
    // m: no. of unqiue elements, n: total elements
    int sortingSol(vector<int>& arr, int k) {
        unordered_map<int, int> freq;
        for(const int num: arr)
            ++freq[num];
        
        // create an array of (freq, element)
        vector<int> element_freq;
        for(auto it = freq.begin(); it != freq.end(); it++)
            element_freq.emplace_back(it->second);
        
        // sort the array in increasing order of freq
        sort(element_freq.begin(), element_freq.end());
        
        // check the number of unique elements that remains after
        // greedily removing the lowest freq elements
        int unique = element_freq.size();
        for(int i = 0; i < element_freq.size(); i++) {
            if(element_freq[i] > k)
                break;
            k = k - element_freq[i];
            --unique;
        }
        
        return unique;    
    }
    
    
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        // sortingSol(arr, k);
        return heapSol(arr, k);
    }
};
