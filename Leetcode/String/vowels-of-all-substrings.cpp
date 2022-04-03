/*
    https://leetcode.com/problems/vowels-of-all-substrings/
    
    sol 1:
    Using the maths based property
    
    sol2: using DP
*/
class Solution {
public:
    bool isVowel(char &ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' 
            || ch == 'o' || ch =='u';
    }
    
    // Sol 1
    // TC: O(N)
    // SC: O(1)
    long long sol1(string &word) {
        long long total = 0;
        
        for(int i = 0; i < word.size(); i++)
            if(isVowel(word[i]))
                // ith char can combine with previous (i-1) chars to form substrings
                // and also {word[i]}. So (i+1) substrings will be formed on the left side (inlcuding single set).
                // Also it will have len - i number of substrings on the right.
                total += (i + 1) * (word.size() - i); 
            
        return total;
    }
    
    // DP sol
    // TC: O(N)
    // SC: O(N)
    long long sol2(string& word) {
        if(word.empty())
            return 0;
        // dp[i] = total no. of vowels found in all the 
        // substrings (only continuous) till with ith char 
        vector<long long> dp(word.size(), 0);
        dp[0] = isVowel(word[0]) ? 1LL : 0LL;
        
        for(int i = 1; i < word.size(); i++) {
            // For the curr char, there will (i+1) substrings in the range [0:i]
            // It will combine with the i-1 substrings that are before + {word[i]}, so if it is a 
            // vowel it will have (i+1) vowel contributions. Also there will be contribution of previously found 
            // vowel chars in the substrings, so we add dp[i-1]
            dp[i] = isVowel(word[i]) ? dp[i-1] + (i + 1): dp[i-1];
        }
        // Each dp[i] has only the vowel contributions of all the substrings with that char,
        // add all such contributions
        return (long long)accumulate(dp.begin(), dp.end(), 0ll);
    }
    
    long long countVowels(string word) {
        // return sol1(word);
        return sol2(word);
    }
};
