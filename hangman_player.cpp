#include "utils.h"
#include "game.h"
#include "leaderboard.h"
#include "history.h"
#include <vector>
#include <algorithm>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define BLUE "\033[0;34m"
#define NORMAL "\033[0m"

int main(int argc, char* argv[]) {
    showHeader();
    std::string playerName;
    if (argc > 1) {
        playerName = argv[1];
        std::cout << GREEN << "Welcome, " << playerName << "! Let's play Hangman!\n" << NORMAL;
    } else {
        std::cout << GREEN << "Enter your name: " << NORMAL;
        std::cin >> playerName;
    }
    std::string wordFile = "words.txt";
    if (argc > 2) {
        wordFile = argv[2];
    }
    std::ifstream file(wordFile);
    if (!file) {
        std::cerr << RED << "Error: Unable to open word file: " << wordFile << NORMAL << std::endl;
        return 1;
    }
    std::string word = getRandomWord(wordFile);
    Game game(word);
    std::vector<char> guessed;
    while (game.tries>0 && !game.complete()) {
        game.show();
        std::cout << CYAN << "Guess a letter: " << NORMAL;
        char c;
        std::cin >> c;
        if (std::find(guessed.begin(), guessed.end(), c) != guessed.end()) {
            std::cout << RED << "Already guessed!\n" << NORMAL;
            continue;
        }
        guessed.push_back(c);
        if (game.guess(c))
            std::cout << GREEN << "Correct!\n" << NORMAL;
        else
            std::cout << RED << "Wrong!\n" << NORMAL;
    }
    if (game.complete()) {
        std::cout << GREEN << "Congrats! Word: " << word << "\n" << NORMAL;
        updateLeaderboard(playerName, true, word);
        updateHistory(playerName, true, word);
    } else {
        std::cout << RED << "Out of tries. Word: " << word << "\n" << NORMAL;
        updateLeaderboard(playerName, false, word);
        updateHistory(playerName, false, word);
    }
    return 0;
}
