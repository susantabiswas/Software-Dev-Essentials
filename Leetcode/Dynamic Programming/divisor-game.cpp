/*
    1025. Divisor Game
    https://leetcode.com/problems/divisor-game/
    
    No matter what is subtracted, when the number is reduced to a prime number then
    only 1 can help, again we might get some divisible number, continuing in this manner
    in the end we they will end up with a smaller prime number. So when the situation is
    like where only 1 can be used and Alice gets an even number then she can win else she losses.
    
    Whoever gets 1 loses. If N is even, Alice picks 1 and the other player gets an odd number.
    No matter even/odd is picked by the other playerm, the num becomes even => going back to prev
    case. If N is odd, Alice picks something, the opponent gets even and he/she can follow the 
    above strategy to make Alice lose.
    The game goes on till someones gets and then they lose.
*/

class Solution {
public:
    bool divisorGame(int N) {
        return N % 2 == 0 ? true : false;
    }
};
