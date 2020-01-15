/*
    https://leetcode.com/problems/top-k-frequent-elements/submissions/
    
    https://leetcode.com/problems/top-k-frequent-elements/discuss/481142/C%2B%2B-Solution-using-Heap-(NlogK)-Detailed-Explanation
*/
class Solution {
public:
    struct Element {
        int val;
        int freq;
        Element(int val, int freq): val(val), freq(freq) {};
        
        // Overload operator
        bool operator>(Element& b) const {
            return freq > b.freq;
        }
    };
    
    // Custom Comparator for heap
    struct Comp {
        bool operator()(const Element& a, const Element& b) {
            return a.freq > b.freq;
        }    
    };
    
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> result;
        // for stroing the frequency of each element
        unordered_map<int, int> num_freq;
        // We will use a min heap of size k
        priority_queue<Element, vector<Element>, greater<>> min_heap;
        
        // priority_queue<Element, vector<Element>, function<bool(Element, Element)>> 
        //     min_heap([](Element a, Element b)->bool {
        //         return a.freq > b.freq;
        //     });
        
        //priority_queue<Element, vector<Element>, Comp> min_heap;
        
        // store the frequency of each number in a hash table
        for(const int& el: nums) {
            if(num_freq.find(el) == num_freq.end())
                num_freq.emplace(el, 0);
            ++num_freq[el];
        }
        
        // traverse through the hash entries, while making sure that heap contains only k elements,
        // since it is a min heap, all smallest frequency elements will be removed at the end, leaving only
        // k most frequent elements
        for(const auto& it: num_freq) {
            min_heap.emplace(Element(it.first, it.second));
            if(min_heap.size() > k)
                min_heap.pop();
        }
        
        // Save the k frequent elements
        while(!min_heap.empty()) {
            result.emplace_back(min_heap.top().val);
            min_heap.pop();
        }
        return result;
    }
};
