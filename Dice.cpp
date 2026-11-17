// Dice.h Functions Implemented

#include "Dice.h"
#include <cstdlib> // Provides std::rand().

void Dice::roll()
{
    // rand() % 6 + 1 = 1 through 6
    die1 = std::rand() % 6 + 1;
    die2 = std::rand() % 6 + 1;
}

int Dice::getDie1() const
{
    return die1;
}

int Dice::getDie2() const
{
    return die2;
}

int Dice::getSum() const
{
    return die1 + die2;
}

bool Dice::isDoubles() const
{
    return die1 == die2;
}
