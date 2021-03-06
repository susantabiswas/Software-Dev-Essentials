/*
    https://leetcode.com/problems/k-closest-points-to-origin/submissions/
*/

class Solution {
    struct CompLess {
        const bool operator()(const vector<int>& a, const vector<int>& b) const {
            return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
        }  
    };
    
    struct CompGreater {
        const bool operator()(const vector<int>& a, const vector<int>& b) const {
            return a[0]*a[0] + a[1]*a[1] > b[0]*b[0] + b[1]*b[1];
        }  
    };
public:
    // Solution1 : Using Max heap
    // TC: O(nlogK)
    vector<vector<int>> solutionHeap1(vector<vector<int>>& points, int K) {
        vector<vector<int>> result;
        // we use a max heap for keeping track of largest distance,
        // traverse the pts and make sure that the heap size is K, removing
        // the largest element each time. In the end we will have K closest points
        priority_queue<vector<int>, vector<vector<int>>, CompLess> max_heap;
        
        // compute the distance and add to heap
        for(auto point: points) {
            max_heap.emplace(point);
            // If size is more, remove the farthest one
            if(max_heap.size() > K) {
                max_heap.pop();
            }
        }    
        
        while(!max_heap.empty()) {
            auto pt = max_heap.top();
            max_heap.pop();
            result.emplace_back(pt);
        }
        
        return result;
    }
    
    // Solution 2: Min heap
    // TC: O(klogn)
    vector<vector<int>> solutionHeap2(vector<vector<int>>& points, int K) {
        vector<vector<int>> result;
        // We use a min heap to keep track of all the closest points
        priority_queue<vector<int>, vector<vector<int>>, CompGreater> 
            max_heap(points.begin(), points.end());   
        
        while(K--) {
            auto pt = max_heap.top();
            max_heap.pop();
            result.emplace_back(pt);
        }
        
        return result;
    }
    
    // Solution 3: Using Partition Algorithm
    // TC: O(N)
    vector<vector<int>> solutionPartition(vector<vector<int>>& points, int K) {
        // We use parititon algorithm to place the Kth element at its correct position
        nth_element(points.begin(), points.begin() + K - 1, points.end(), 
            [](const vector<int>& a, const vector<int>& b)->bool{
                return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
            });
        return vector<vector<int>>{points.begin(), points.begin() + K};
    }
    
    // Solution 4: Using Stable Sort
    // TC: O(NlogK)
    vector<vector<int>> solutionPartialSort(vector<vector<int>>& points, int K) {
        // We sort the array partially
        partial_sort(points.begin(), points.begin() + K, points.end(), 
            [](const vector<int>& a, const vector<int>& b)->bool{
                return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
            });
        return vector<vector<int>>{points.begin(), points.begin() + K};
    }
    
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        // return solutionHeap1(points, K);
        // return solutionHeap2(points, K);
        // return solutionPartition(points, K);
        return solutionPartialSort(points, K);
    }
};
