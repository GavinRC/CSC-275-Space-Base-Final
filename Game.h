#ifndef CSC_275_SPACE_BASE_FINAL_GAME_H
#define CSC_275_SPACE_BASE_FINAL_GAME_H
#include <string>
#include <vector>
#include "Player.h"
#include "Card.h"
#include "Shipyard.h"
#include "Die.h"
class Game {
private: // Private Variables
    std::vector<Player*> players;
    std::vector<std::string> turnOrder;
    std::vector<Card*> allCards;
    Shipyard shipyard;
    int vpGoal;

    // Private Methods
    void takeTurn(Player* activePlayer);
    void payOut(Player* player, std::vector<int> sectors, bool isActive);
    Player* findWinner();

public: // Public Methods
    Game(std::string cardFile, int vpGoal);
    ~Game();
    void play();
};
#endif //CSC_275_SPACE_BASE_FINAL_GAME_H
