#include "leaderboard.h"
#include "history.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string command = argv[1];
        if (command == "view_history") {
            if (argc > 2) {
                displayHistory(argv[2]);
            } else {
                displayHistory();
            }
        } else if (command == "view_leaderboard") {
            displayLeaderboard();
        } else {
            std::cout << "Unknown command.\nUsage:\n  hangman_host view_history [PlayerName]\n  hangman_host view_leaderboard\n";
        }
    } else {
        std::cout << "Usage:\n  hangman_host view_history [PlayerName]\n  hangman_host view_leaderboard\n";
    }
    return 0;
}
