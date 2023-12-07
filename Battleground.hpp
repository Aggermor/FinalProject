#ifndef BATTLEGROUND_HPP_INCLUDED
#define BATTLEGROUND_HPP_INCLUDED

#include "Opponent.hpp"

class Battleground
{
private:
    Player* objectPlayerPtr;
    Opponent* objectOpponentPtr;

    Monster* objectPlayerMonsterPtr_;   // player's monster "on deck"
    Monster* objectOpponentMonsterPtr_;     // opponent's monster "on deck"
public:
    // constructors
    Battleground();
    Battleground(Player objectPlayer_, Opponent objectOpponent_);
    ~Battleground();

    // member functions
    bool battleCriticalHit(int chance_);

    double getBattleAttack(Monster* objectMonsterAttack_, Monster* objectMonsterDefend_);
    void healCheck(Monster* objectMonster_);

    void choosePlayerMonsterToFight();
    void chooseOpponentMonsterToFight();

    int battleInput();
    void battleLoop();
    void battleInterface();
    void battleCheck();
    bool battleResult();
    void battleInventory(int sizeMonster);
};

#endif // BATTLEGROUND_HPP_INCLUDED
