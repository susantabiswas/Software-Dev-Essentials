/*
    https://leetcode.com/problems/sort-colors/
    
    We use three pointers, red, white and blue. White ptr is used
    for traversing the array and blue, red ptrs used for writing the 
    blue and red elements respectively. Incase a white is discovered,
    the white ptr simply increments its position.
    After the loop ends, below will be the state of pointers
    [0 : RED - 1] [RED : BLUE] [WHITE : N-1]
            ^           ^              ^
            |           |              |
            Red        White          Blue
*/
class Solution {
public:
    // TC: O(N), SC: O(1)
    void sortColors(vector<int>& nums) {
        // red: position where red will be written
        // white: position where white will be written
        // blue: position before the last written blue element
        int red = 0, white = 0, blue = nums.size();
        
        while(white < blue) {
            // write the red color at its latest writable position
            if(nums[white] == 0)
                swap(nums[red++], nums[white++]);
            // keep white and increment the writable index of white
            else if(nums[white] == 1)
                ++white;
            // write the blue at its position by swapping, don't increment
            // writeable index of white, incase after swapping it is found that
            // current is red
            else if(nums[white] == 2)
                swap(nums[white], nums[--blue]);
        }
    }
};
