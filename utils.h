#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

#define RED "\033[0;31m"
#define CYAN "\033[0;36m"
#define NORMAL "\033[0m"

inline void showHeader() {
    std::cout << RED << "\n----------------------\n" << NORMAL;
    std::cout << CYAN << "H A N G M A N   G A M E" << NORMAL;
    std::cout << RED << "\n----------------------\n" << NORMAL;
}

inline std::string getRandomWord(const std::string& filename) {
    std::ifstream file(filename);
    int count;
    file >> count;
    std::vector<std::string> words(count);
    for (int i=0; i<count; i++) file >> words[i];
    srand(time(0));
    return words[rand()%count];
}

#endif
