/*
    https://leetcode.com/problems/4sum/
    
    SOLUTION 1: TLE
    Idea is to use a multi map to save the number pairs, if 
    there exists a + b + c + d = target, then that means we will see 4 diff numbers.
    So we use two loops to pick a pair of numbers, initially when we had a and b, we look for target - (a+b)
    in the hash table, it might not be there, then push the current pair, so when we are at c and d and look
    for target - (c+d), that time we will get the (a,b) pair in the hash table. 
    
    TC: O(N^2) + O(NlogN)
    SC: O(N)
    
    SOLUTION 2: Generalized K sum
    For k sum problem, we need k-2 loops for selecting the different variables. The last 2 can be selected by 2 sum solution. Making the TC => O(n^k-1).
    To mimic the k-2 loops we can use recursion.
*/
class Solution {
public:
    // TLE now 
    vector<vector<int>> sol1(vector<int>& arr, int target) {
        vector<vector<int>> result;
        multimap<int, pair<int, int>> mp;
        set<vector<int>> s;

        for(int i = 0; i < arr.size(); i++) {
            for(int j = i + 1; j < arr.size(); j++) {
                // a + b = target - (c + d)
                // check if target - (c + d) exists in hash table
                int sum = arr[i] + arr[j];
                auto res = mp.equal_range(target - sum);

                for(auto it = res.first; it != res.second; it++) {
                    int a = it->second.first;
                    int b = it->second.second;
                    
                    // check if the numbers are diff index wise also
                    if(a != i && a != j && b != i && b != j) {
                        vector<int> quadruplet = 
                            {arr[a], arr[b], arr[i], arr[j]};

                        sort(begin(quadruplet), end(quadruplet));
                        if(s.find(quadruplet) == s.end()) {
                            s.emplace(quadruplet);
                            result.emplace_back(move(quadruplet));
                        }
                    }
                }
                // insert the current pair
                mp.emplace(make_pair(sum, make_pair(i, j)));
            }
        }

        return result;
    }
    
    vector<vector<int>> kSum(int k, int start, long long target, vector<int>& nums) {
        vector<vector<int>> result;
        // Base cases:
        
        // Base Case: No elements left
        if(start == nums.size())
            return result;
        // Base case: Since the array elements are sorted, we can quickly check if it is 
        // even possible to get the target sum with the numbers lying ahead
        long avg = target / k;
        // If the starting number (smallest) itself is greater than avg, then remaining k-1 numbers will definitely 
        // have sum > target
        // If the ending number (greatest) itself is smaller than the avg, remaining k-1 will have sum < target
        if(nums[start] > avg || nums.back() < avg)
            return result;
        // If we have just k = 2, we can use 2Sum solution. We can either use the hashing or two pointers solution for 2Sum
        if(k == 2)
            return twoSum(nums, target, start);
        
        // Run the kth loop for selecting the kth number
        for(int i = start; i < nums.size(); ++i) {
            if(i == start || nums[i] != nums[i-1]) {
                // Get the result for k-1Sum problem and combine with the selection for the kth loop
                auto subsets = kSum(k-1, i+1, target - nums[i], nums);
                // Add the kth number with all the k-1 results
                for(auto subset: subsets) {
                    result.emplace_back(vector<int>{nums[i]});
                    // Add the k-1Sum result 
                    result.back().insert(result.back().end(), subset.begin(), subset.end());
                }
            }
        }
        return result;
    }
  
    vector<vector<int>> twoSum(vector<int>& nums, long long target, int start) {
        vector<vector<int>> pairs;
        
        int end = nums.size() - 1;
        while(start < end) {
            int sum = nums[start] + nums[end];
            if(sum == target) {
                pairs.emplace_back(vector<int>{nums[start], nums[end]});
                ++start, --end;    
                // skip duplicates
                while(start < end && nums[start] == nums[start-1])
                    ++start;
                while(end > start && nums[end] == nums[end+1])
                    --end;
            }
            else if(sum < target)
                ++start;
            else
                --end;
            
        }
        return pairs;
    }
    
    // SOLUTION 2: Generalized k Sum
    // TC: O(nlogn + n^k-1) ~ O(n^3)
    // SC: O(n)
    vector<vector<int>> sol2(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        return kSum(4, 0, (long long)target, arr);
    }
    
    
    vector<vector<int>> fourSum(vector<int>& arr, int target) {
        // return sol1(arr, target);
        return sol2(arr, target);
    }
};
