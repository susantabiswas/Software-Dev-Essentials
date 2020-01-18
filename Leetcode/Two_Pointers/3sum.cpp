/*
    https://leetcode.com/problems/3sum/
    
    Sort the array. Idea is to traverse through the array, fixing the current 
    number as the first number. Take this as -ve of sum to search for in the remaining 
    array. b + c = -a. The problem asks for unique triplets, so duplicates should be ignored.
    Skip the duplicates for second and third number while finding the solutions. 
    For the next first number again skip any duplicates found
    
*/
class Solution {
public:
    // TC: O(N^2)
    vector<vector<int>> threeSum(vector<int> arr) {
        vector<vector<int> > result;
        // sort the array
        sort(arr.begin(), arr.end());
        
        // this will be the first number 'a'
        int i = 0;
        while(i < arr.size()) {
            // since the sum should be zero, and the array is sorted
            // so if the first number itself is +ve, then remaining will also be +ve
            // making it impossible to have a sum of 0
            if(arr[i] > 0)
                break;
            
            // We use 'a' for finding b + c such that b + c = -a
            int start = i + 1, end = arr.size() - 1;
            while(start < end) {
                int sum = arr[start] + arr[end];
                
                if(sum < -arr[i])
                    ++start;
                else if(sum > -arr[i])
                    --end;
                else {
                    // when a triplet is found 
                    result.emplace_back(vector<int>{arr[i], arr[start], arr[end]});
                    ++start, --end;
                    // skip all the duplicates of second and third numbers
                    while(start < end && arr[start] == arr[start - 1])
                        ++start;
                    while(end > start && arr[end] == arr[end + 1])
                        --end;
                }
            }
            
            ++i;
            // skip all the duplicates of arr[i]
            while(i < arr.size() && arr[i] == arr[i-1])
                ++i;
        }
        return result;
    }
};
