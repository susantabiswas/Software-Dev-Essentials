/*
    https://leetcode.com/problems/design-parking-system/
    
    TC: O(1)
    SC: O(1)
    
    Idea is to just track the 3 slot counts for each of the car types.
    To make code concise and ready for future upgrades, use a hash table.
*/
class ParkingSystem {
private:
    unordered_map<int, int> slots;
public:
    ParkingSystem(int big, int medium, int small) {
        slots[1] = big;
        slots[2] = medium;
        slots[3] = small;
    }
    
    bool addCar(int carType) {
        if(slots[carType] > 0) {
            --slots[carType];
            return true;
        }
        return false;
    }
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
