// Dice Class

#ifndef DICE_H
#define DICE_H

class Dice
{
private:
    // Private variables to keep dice values protected from outside changes
    int die1 = 1;
    int die2 = 1;

public:
    void roll();                 // Rolls both dice.
    int getDie1() const;         // Returns the first die.
    int getDie2() const;         // Returns the second die.
    int getSum() const;          // Returns their combined value.
    bool isDoubles() const;      // Checks whether both values match.
};



#endif
