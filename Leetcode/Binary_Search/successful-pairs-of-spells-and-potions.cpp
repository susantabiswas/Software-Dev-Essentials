/*
    https://leetcode.com/problems/successful-pairs-of-spells-and-potions/
    
    TC: O(mlogm + nlogn), m = size of potions, n = size of spells
    SC: O(m), for sorting
    
    The ask is to find the smallest and largest potion for each spell, then whatever
    lies in this range can form valid pairs with the spell.
    
    - We can sort the potions array.
    - Then for each spell, we find the lower index in potion array which satisfies the condition.
    Since the potion array was sorted earlier, we can binary search to do this.
*/
class Solution {
public:
    // VARIANT 1
    long lowerBound(vector<int>& arr, int target, long success) {
        int low = 0;
        // NOTE: We can taken the lastIndex + 1 as the right, this allows processing of array
        // even with just a single element
        int high = arr.size();
        
        while(low < high) {
            int mid = low + (high - low) / 2;
            long product = (long)arr[mid] * target;
            
            // a valid answer found, safely make this the upper bound
            if(product >= success) 
                high = mid;
            else
                low = mid + 1;
        }
        // check if a valid answer was found
        return high == arr.size() ? -1 : high;
    }
    
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());
        int upper = potions.size();
        
        vector<int> result(spells.size(), 0);
        
        for(int i = 0; i < spells.size(); i++) {
            int spell = spells[i];
            long lower = lowerBound(potions, spell, (long)success);
            result[i] = lower != -1 ? upper - lower : 0;
        }
        return result;
    }

//////////////////////////// VARIANT 2 //////////////////
long lowerBound(vector<int>& arr, int target, long success) {
        int low = 0, high = arr.size();
        
        while(low < high) {
            int mid = low + (high - low) / 2;
            
            long product = (long)arr[mid] * target;
            if(product >= success) {
                high = mid;
            }
            else
                low = mid + 1;
        }
  // lower index will always point to a valid answer index
  // high always points to a valid answer index, if the current mid doesnt satisfy
  // the condition, the index low will move towards high and keep moving till it is equal to high
  // in the end loop
        return low;
    }
    
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());
        int upper = potions.size();
        
        vector<int> result(spells.size(), 0);
        
        for(int i = 0; i < spells.size(); i++) {
            int spell = spells[i];
            long lower = lowerBound(potions, spell, (long)success);
            result[i] = upper - lower;
        }
        return result;
    }
};
