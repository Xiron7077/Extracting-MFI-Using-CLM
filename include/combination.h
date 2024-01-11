#ifndef COMBINATION
#define COMBINATION

#include <iostream>
#include <vector>
#include <string>

// Global vector
std::vector<std::pair<std::string, int>*> combinations;

// Generate all possible combination
void generateCombinations(const std::string& input, std::string& current, int index) {

    // Check if combination is not null
    if(current != " "){
        // Check is the vector is empty
        if(combinations.empty()){
            // Create a new pair and push back into vector
            auto* new_pair = new std::pair<std::string, int>(current, 1);
            combinations.push_back(new_pair);
        } else {
            // Check if pair is already present
            bool is_present = false;
            for(std::pair<std::string, int>* pair : combinations){
                if(pair->first == current){
                    // Increments the counter if present
                    pair->second ++;
                    is_present = true;
                }
            }
            if(!is_present){
                // Create a new pair and push back into vector
                auto* new_pair = new std::pair<std::string, int>(current, 1);
                combinations.push_back(new_pair);
            }
        }
    }

    // Iterate through the remaining characters in the input string
    for (int i = index; i < input.length(); ++i) {
        // Include the current character in the combination
        current.push_back(input[i]);

        // Recursively generate combinations starting from the next index
        generateCombinations(input, current, i + 1);

        // Backtrack: remove the last character to explore other combinations
        current.pop_back();
    }
}

// Calls the generate function
void findAllCombinations(const std::string& input) {
    std::string current = "";
    generateCombinations(input, current, 0);
}

#endif // COMBINATION