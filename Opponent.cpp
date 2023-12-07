/* Opponent */

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Monster.hpp"
#include "Player.hpp"
#include "Opponent.hpp"


using namespace std;

// cosntructor
Opponent::Opponent() : Player()
{

}

// member functions
Monster Opponent::selectMonster()
{
    //srand(time(0));
    //cout << monsterInventory[rand()%3];
    return monsterInventory[rand() % (monsterInventory.size())];
}

int Opponent::randomChoice(Monster* objectMonster_)
{
    if(objectMonster_ -> getHealth() == objectMonster_ -> getMAX_HEALTH())
    {
        return 1;
    }
    else
    {
        int choiceWeigth[10] = { 1, 1, 1, 1, 1, 1, 1, 2, 2, 2 };
        return choiceWeigth[rand() % 10]; // only two possible choices: 1 for attack, 2 for heal the chance to heal is lower.
    }

}
