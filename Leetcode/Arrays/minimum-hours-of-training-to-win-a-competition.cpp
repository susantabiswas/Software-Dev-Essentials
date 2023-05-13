/*
    https://leetcode.com/problems/minimum-hours-of-training-to-win-a-competition/
    
    TC: O(N)
    SC: O(1)
    
    To find the min extra training hours, we start traversing through the opponents and 
    check if the current exp or energy value is lesser than the current opponent's values.
    If it is, then we need abs(diff) + 1 amount to become strictly greater than the opponents's values.
    
    While updating the energy and exp values, ensure that we account for the addition training hrs if added.
*/
class Solution {
public:
    int minNumberOfHours(int initialEnergy, int initialExperience, vector<int>& energy, vector<int>& experience) {
        int hrs = 0;
        
        for(int i = 0; i < energy.size(); i++) {
            // If any of the values is higher, we need the extra number to win 
            if(energy[i] >= initialEnergy)
                hrs += abs(energy[i] - initialEnergy) + 1;
            if(experience[i] >= initialExperience)
                hrs += abs(experience[i] - initialExperience) + 1;
            
            // update the new values accounting for the scenario where we had to add more training hours
            // to become strictly greater.
            // To win we add the abs(diff) + 1, so after subtracting the energy, we will be left with a 1
            initialEnergy = energy[i] >= initialEnergy ? 1 : initialEnergy - energy[i];
            // For experience, in case we fell short of experience, we need to add abs(diff) + 1 as well
            initialExperience = initialExperience + experience[i] + 
                        (experience[i] >= initialExperience ? abs(experience[i] - initialExperience) + 1 : 0);
        }
        
        return hrs;
    }
};
