/*
    1025. Divisor Game
    https://leetcode.com/problems/divisor-game/
    
    No matter what is subtracted, when the number is reduced to a prime number then
    only 1 can help, again we might get some divisible number, continuing in this manner
    in the end we they will end up with a smaller prime number. So when the situation is
    like where only 1 can be used and Alice gets an even number then she can win else she losses.
    
*/

class Solution {
public:
    bool divisorGame(int N) {
        return N % 2 == 0 ? true : false;
    }
};
