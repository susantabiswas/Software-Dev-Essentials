/*
    https://leetcode.com/problems/duplicate-zeros/
    
    TC: O(N), SC: O(1)
    
    Since each zero needs to be updated with two zero entries adjacent, the array will increase in length
    by an amount equal to number of zeros.
    So find the total number zeros, then we assume we have an array with enough space to accomodate every element.
    We use an index write_idx at the back of this imaginary array and another ptr curr at the end of actual array arr[N-1].
    We start from back and for each element we assume that we are writing it to its actual position, but we write only if the
    write_idx < N, but we keep updating the write_idx as if we actual wrote something.
    For any zero write twice.
*/
class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        const int N = arr.size();
        // find the count of zeros
        int num_zeros = count(arr.begin(), arr.end(), 0);
        // index where elements will be written
        int write_idx = N + num_zeros - 1; 
        // current travering index
        int curr = N - 1;
        
        while(curr >= 0 && write_idx >= 0) {
            // write the current element to its correct position,
            // iff that is within N size
            if(write_idx < N)
                arr[write_idx] = arr[curr];
            
            write_idx -= 1;
            // if the current element is also a zero, write again its duplicate
            if(arr[curr] == 0) {
                if(write_idx < N)
                    arr[write_idx] = 0;
                write_idx -= 1;
            }
            --curr;
        }
    }
};
