#include "Game.h"
#include "ShipCard.h"
#include "Reward.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game(std::string cardFile, int vpGoal) {
    this->vpGoal = vpGoal;
    srand(time(0));

    shipyard.loadCards(cardFile, allCards);
    int numPlayers = 0; // Temporarily variable to record how many players there are
    std::cout << "How many players are playing?: (2-5)";
    std::cin >> numPlayers;

    for (int i = 1; i <= numPlayers; i++) {
        std::string playerName;
        std::cout << "Enter player "<<i << "'s name: ";
        std::cin >> playerName;
        if (playerName.empty()) {
            playerName = "Player " + std::to_string(i);
        }

        std::vector<Card*> starters;
        for (int sector = 1; sector <= 12; sector++) {
            int credits = 1;
            if (sector >= 7) {
                credits = 2;
            }

            Card* starter = new ShipCard("Starter Ship", 0, sector, 0, Reward(credits, 0, 0), Reward(1, 0, 0));

            allCards.push_back(starter);
            starters.push_back(starter);
        }

        players.push_back(new Player(playerName, starters));
        turnOrder.push_back(playerName);
    }
}

Game::~Game() {
    for (int i = 0; i < players.size(); i++) {
        delete players[i];
    }
    for (int i = 0; i < allCards.size(); i++) {
        delete allCards[i];
    }
}

void Game::play() {
    std::cout <<"\n=== SPACE BASE ===\n";
    std::cout << "First to " << vpGoal << " VP wins. Turn order: ";
    for (int i = 0; i < turnOrder.size(); i++) {
        std::cout << turnOrder[i];
        if (i < turnOrder.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    int round = 1;
    Player* winner = nullptr;

    while (winner == nullptr) {
        std::cout << "\n----- ROUND " << round << " -----\n";
        for (int i = 0; i < players.size(); i++) {
            takeTurn(players[i]);
        }
        winner = findWinner();
        round++;
    }

    std::cout << "\n=== GAME OVER ===\n";
    for (int i = 0; i < players.size(); i++) {
        std::cout << players[i]->getName() << ": " << players[i]->getVP() << "VP\n";
    }
    std::cout << winner->getName() << " wins!\n";
}

void Game::takeTurn(Player* activePlayer) {
    std::cout << "\n" << activePlayer->getName() << "'s turn\n";
    std::cout << *activePlayer << std::endl; // friend operator<< shows their board


    // 1. Roll the dice
    die.roll();
    int die1 = die.getDie1();
    int die2 = die.getDie2();

    std::cout << "Rolled " << die1 << " and " << die2 << " (sum " << die1 + die2 << ")\n";

    // 2. Every player picks sum or separate, then collects rewards
    for (int i = 0; i < players.size(); i++) {
        bool isActive = (players[i] == activePlayer);
        std::vector<int> sectors = players[i]->chooseSectors(die, isActive);
        payOut(players[i], sectors, isActive);
    }

    // 3. Active player may buy one card (nullptr means they passed)
    Card* choice = activePlayer->chooseCard(shipyard);
    if (choice != nullptr) {
        if (activePlayer->buy(choice)) {
            shipyard.take(choice);
            std::cout << activePlayer->getName() << " bought " << choice->getName() << std::endl;
        } else {
            std::cout << "Not enough credits to buy " << choice->getName() << std::endl;
        }
    }

    // 4. Credits top up to income if they are below it
    activePlayer->endTurnIncome();
}

void Game::payOut(Player* player, std::vector<int> sectors, bool isActive) {
    Reward earned;
    for (int i = 0; i < sectors.size(); i++) {
        if (isActive) {
            earned += player->getConsole().activeReward(sectors[i]);    // blue station rewards
        } else {
            earned += player->getConsole().passiveReward(sectors[i]);   // red deployed rewards
        }
    }
    *player += earned;
    std::cout << player->getName() << " earned " << earned << std::endl;
}