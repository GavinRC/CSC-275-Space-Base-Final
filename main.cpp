// Temporary and only to see the die class

#include <iostream>
#include <cstdlib> // std::srand().
#include <ctime>   // std::time().
#include "Dice.h"

int main()
{
    // Seed once so separate runs can produce different dice sequences.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Dice dice; // Creates one object containing two dice.
    dice.roll();

    // Uses public functions to read the private dice values.
    std::cout << "Die 1: " << dice.getDie1() << '\n';
    std::cout << "Die 2: " << dice.getDie2() << '\n';
    std::cout << "Total: " << dice.getSum() << '\n';

    if (dice.isDoubles())
    {
        std::cout << "You rolled doubles!\n";
    }

    return 0; 
}
