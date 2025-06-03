#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <iostream>
#include <fstream>
#include <map>
#include <string>

inline void updateLeaderboard(const std::string& playerName, bool win, const std::string& word) {
    std::map<std::string, int> leaderboard;
    std::ifstream infile("leaderboard.txt");
    std::string name;
    int score;
    while (infile >> name >> score) {
        leaderboard[name] = score;
    }
    infile.close();
    if (win) leaderboard[playerName] += word.size();
    else if (leaderboard.find(playerName) == leaderboard.end()) leaderboard[playerName] = 0;
    std::ofstream outfile("leaderboard.txt");
    for (auto& entry : leaderboard) {
        outfile << entry.first << " " << entry.second << "\n";
    }
}

inline void displayLeaderboard() {
    std::ifstream file("leaderboard.txt");
    if (!file) {
        std::cout << "No leaderboard data available.\n";
        return;
    }
    std::string line;
    std::cout << "=== Leaderboard ===\n";
    while (getline(file, line)) {
        std::cout << line << "\n";
    }
}

#endif
