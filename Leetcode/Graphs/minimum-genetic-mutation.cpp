/*
    https://leetcode.com/problems/minimum-genetic-mutation/
    
    TC: O(BL + C^L * (LC * L)), 
    To add the genes from bank to set takes O(BL)
    
    There are C^L possible states, which we will end up iterating through because of 
    the loops. In the worst case they all can be part of bank.
    Also for each state, we have a 2 nested loops = LC
    Also operation with str takes O(L)
    
    Also for each of the genes, we iterate through all the positions and then put
    all the possible gene chars at that position. (L * C)
    
    SC: O((LB + CL))
    For each gene we can have L*C valid mutations if they all are in the bank
    L = Length of gene
    C = No. of unique letters in gene
    B = Max no. of genes in bank
*/
class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        vector<char> chars = {'A', 'C', 'G', 'T'};
        
        // <gene, mutations>
        queue<pair<string, int>> q;
        unordered_set<string> valid_genes(bank.begin(), bank.end());
        
        q.push({startGene, 0});
        // mark as visited
        if(valid_genes.count(startGene))
            valid_genes.erase(startGene);
        
        while(!q.empty()) {
            auto [gene, mutations] = q.front();
            q.pop();
            
            if(gene == endGene)
                return mutations;
            
            string mutated_gene(gene);
                
            // introduce mutations at each position
            for(int i = 0; i < gene.size(); i++) {
                char orig = mutated_gene[i];
                
                for(auto ch: chars) {
                    mutated_gene[i] = ch;
                    
                    // this mutation will be allowed, if it is in the gene bank
                    if(valid_genes.count(mutated_gene)) {
                        q.push({mutated_gene, mutations + 1});
                        valid_genes.erase(mutated_gene);
                    }
                }
                // revert the change
                mutated_gene[i] = orig;
            }
        }
        return -1;
    }
};
