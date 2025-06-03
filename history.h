#ifndef HISTORY_H
#define HISTORY_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>

inline void updateHistory(const std::string& playerName, bool win, const std::string& word) {
    std::ifstream infile("history.txt");
    std::map<std::string, std::pair<int, int>> counts;
    std::map<std::string, std::vector<std::pair<char, std::string>>> guesses;
    std::string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string name;
        int correct, wrong;
        if (iss >> name >> correct >> wrong) {
            counts[name] = {correct, wrong};
            for (int i = 0; i < correct + wrong; i++) {
                getline(infile, line);
                if (!line.empty() && (line[0]=='R' || line[0]=='W')) {
                    guesses[name].emplace_back(line[0], line.substr(2));
                }
            }
        }
    }
    infile.close();
    if (counts.find(playerName) == counts.end()) {
        counts[playerName] = {0, 0};
    }
    if (win) counts[playerName].first++;
    else counts[playerName].second++;
    if (guesses.find(playerName) == guesses.end()) {
        guesses[playerName] = {};
    }
    guesses[playerName].emplace_back(win ? 'R' : 'W', word);
    std::ofstream outfile("history.txt");
    for (auto& entry : counts) {
        outfile << entry.first << " " << entry.second.first << " " << entry.second.second << "\n";
        for (auto& g : guesses[entry.first]) {
            outfile << g.first << " " << g.second << "\n";
        }
    }
}

inline void displayHistory(const std::string& targetPlayer = "") {
    std::ifstream infile("history.txt");
    if (!infile) {
        std::cout << "No history data available.\n";
        return;
    }
    std::map<std::string, std::pair<int, int>> counts;
    std::map<std::string, std::vector<std::pair<char, std::string>>> guesses;
    std::string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string name;
        int correct, wrong;
        if (iss >> name >> correct >> wrong) {
            counts[name] = {correct, wrong};
            for (int i = 0; i < correct + wrong; i++) {
                getline(infile, line);
                if (!line.empty() && (line[0]=='R' || line[0]=='W')) {
                    guesses[name].emplace_back(line[0], line.substr(2));
                }
            }
        }
    }
    infile.close();
    bool found = false;
    std::cout << "=== History ===\n";
    for (const auto& entry : counts) {
        const std::string& name = entry.first;
        if (!targetPlayer.empty() && name != targetPlayer) continue;
        found = true;
        std::cout << "\nPlayer: " << name << "\n";
        std::cout << " Wins: " << entry.second.first << ", Losses: " << entry.second.second << "\n";
        std::cout << " Guesses:\n";
        for (const auto& g : guesses[name]) {
            std::cout << "  [" << (g.first == 'R' ? "Win" : "Loss") << "] Word: " << g.second << "\n";
        }
    }
    if (!found && !targetPlayer.empty()) {
        std::cout << "No history found for player: " << targetPlayer << "\n";
    }
}

#endif
