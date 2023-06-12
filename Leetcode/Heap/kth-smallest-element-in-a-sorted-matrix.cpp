/*
    https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
    
    TC: O(klogk)
    SC: O(k)
    
    Idea is very similar to the merging k sorted arrays. Since the rows and cols are
    sorted, we can treat the rows as sorted individual arrays.
    We use a min heap of size k, starting with the 1st element from each row.
    Popping the elements from heap k-1 times, pushing the next element of popped element if 
    that exists.
    
    In case two row values are same, we pick the next row value with higher column index, since
    elements increase column wise as well
*/
class Solution {
public:
    int kthSmallest(vector<vector<int>>& nums, int k) {
        int num_arrays = nums.size();
        
        using vector_it = vector<int>::const_iterator;

        // Custom comparator, uses the current running iterator's value to compare
        auto comp = [&](const tuple<vector_it, vector_it, int> it1, 
                        const tuple<vector_it, vector_it, int> it2) { 
            // If both have the same value, pick the column with higher index
            // as values as sorted column wise as well so the higher column might
            // have a bigger next value
            if(*(get<0>(it1)) == *(get<0>(it2)))
                return get<2>(it1) < get<2>(it2);
            return *(get<0>(it1)) > *(get<0>(it2)); 
        };
        // create a min heap that tracks num_arrays elements at a time
        // <iterator, iterator end, array index to which belongs>
        priority_queue<tuple<vector_it, vector_it, int>, 
            vector<tuple<vector_it, vector_it, int>>, decltype(comp)> 
        min_heap(comp);
        
        // Add the first element from each array
        for(int idx = 0; idx < num_arrays; idx++)
            if(!nums[idx].empty()) {
                min_heap.emplace(make_tuple(nums[idx].cbegin(), nums[idx].cend(), idx));
            }
        
        // Everytime pop the smallest element, if there is another element in the same array
        // that is pushed
        // Pop the elements k-1 times
        while(k-- > 1 && !min_heap.empty()) {
            auto [curr_it, end_it, arr_idx] = min_heap.top();
            min_heap.pop();
            
            // If next element exists, push to heap
            if(next(curr_it) != end_it)
                min_heap.emplace(make_tuple(next(curr_it), end_it, arr_idx));
        }
        // Get the kth element
        return *get<0>(min_heap.top());
    }
};


//////////////////////////////// SOLUTION 2: Binary Search
class Solution {
public:
    // SOLUTION: Binary Search
    // TC: O((m+n)log(S)), 
    // SC: O(1)
    // m = no. of rows, n = no. of cols, S = Search space (MaxNumber (bottom right) - MinNumber (top left))
    /*
        The idea is to use binary search on the search space range. In this case
        search space is MinNumber..MaxNumber of matrix i.e top left to bottom right.
        
        Then we find a candidate number and check how many elements in the matrix are <= candidate.
        Since the candidate may or may not be in the matrix, we look for the smallest candidate for
        which there are atleast <= k no. of elements <= candidate.
        
        Proof why the final candidate will always exist in the matrix
        
        When we generate a number between the lower and upper bound, it might not necessarily be present in the
        matrix but can still satisfy the BSearch criteria. So we look for the next smaller candidate satisying the 
        criteria and keeping looking the smallest till the next candidate breaks the criteria.
        
        When one of the candidates actually exists, then any number less than that won't satisfy the criteria
        of count(candidate) >= k. This is because if X is the actual candidate that exists in the matrix, then all the 
        numbers > x, were seeing the contribution of count till x and were getting count(candidate) = y (which is >= k).
        But any number < x, won't get the count contribution of x anymore and hence the count(candidate) < k (since x is not counted)
        
        nums = [1, 2, 20, 30, 30, 70, 80, 100], k = 5, ans should be 30
        
        !!! NOTE: Showing some scenarios, the candidates are not generated as per binary search, just showing why a smaller candidate will exist
        
        Let'say we generate a mid candidate 70 (doesnt exist) and it satisfies the count condition
        countLessThanEqual(70) = 6 which is >= k, so right = 70
        
        Next candidate is say 50 (doesnt exist), countLessThanEqual(50) = 6 which is >= k, right = 50
        Next candidate is say 30 (exists), countLessThanEqual(30) = 5 which is >= k, right = 30
        Next candidate is say 20 (exists), countLessThanEqual(20) = 3 which is < k (the actual answer 30 was excluded and hance made the count < k)
        
        
        
    */
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        
        // lower and upper bound for binary search
        int l = matrix[0][0], r = matrix[m-1][n-1];
        
        // Kth smallest element will have k elements(incl. itself) <= than itself
        while(l < r) {
            int mid = l + (r - l) / 2;
            
            // Since the current candidate's count >= k,
            // it is a likely ans. If there are duplicates in the matrix
            // then that explains > k part or if it is the exact
            // answer then == k, so we make the upper bound as this likley ans candidate
            if(countLessThanEqual(matrix, mid) >= k)
                r = mid;
            else
                // Since count < k, no chance this is the ans candidate, safely ignore
                // mid
                l = mid + 1;
        }
        return r;
    }
    
    // The reason why we count the equal elements as well is because
    // those also contributes to the kth count
    // eg [1, 2, 2, 2], k = 3, ans = 2, unless we count the 1st 2, we cannot conclude
    // that the 2nd 2 is the 3rd smallest number
    // TC: O(row + col)
    int countLessThanEqual(vector<vector<int>>& matrix, int mid) {
        int col = matrix[0].size() - 1;
        // Tracks the no. of elements <= k
        int count = 0;
        
        for(int row = 0; row < matrix.size(); row++) {
            while(col >= 0 && matrix[row][col] > mid)
                --col;
            
            // now matrix[row][col] is <= k, so all the elements
            // in the current row from [0..col] are <= k
            count += col + 1;
        }
        
        return count;    
    }
};
