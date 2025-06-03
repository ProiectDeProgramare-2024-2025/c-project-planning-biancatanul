#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define YELLOW "\033[0;33m"
#define NORMAL "\033[0m"

class Game {
public:
    std::string word, hiddenWord;
    int tries;
    Game(std::string w) : word(w), tries(5) {
        hiddenWord = std::string(word.size(), '_');
        hiddenWord[0] = word[0];
        hiddenWord[word.size()-1] = word[word.size()-1];
    }
    bool guess(char c) {
        bool found = false;
        for (size_t i = 0; i < word.size(); i++)
            if (word[i]==c && hiddenWord[i]=='_') {
                hiddenWord[i]=c;
                found=true;
            }
        if (!found) tries--;
        return found;
    }
    bool complete() {
        return word == hiddenWord;
    }
    void show() {
        std::cout << YELLOW << "Word: " << hiddenWord << " (Tries left: " << tries << ")" << NORMAL << "\n";
    }
};

#endif
