#include <iostream>
#include <vector>
#include "Monster.hpp"
#include "Player.hpp"

/* Player */

// constructor
Player::Player()
{
    name = "NA";
}

Player::Player(string name_)
{
    name = name_;
}

// getters
string Player::getName() const
{
    return name;
}

vector<Monster> Player::getMonsterInventory()
{
    return monsterInventory;
}

int Player::getSize() const
{
    return monsterInventory.size();
}

// setters
void Player::setName(string name_)
{
    name = name_;
}

// indexing
void Player::addMonster(Monster objectMonster_)
{
    monsterInventory.push_back(objectMonster_);
}

void Player::removeMonster(Monster objectMonster_)
{
    for(int i = 0; i < monsterInventory.size(); i++)
    {
        if(monsterInventory[i] == objectMonster_)
        {
            monsterInventory.erase(monsterInventory.begin()+i);
            break;
        }
    }
}

void Player::updateMonsterInVector(Monster* objectMonster_)
{

    bool found = false;
    for(int i = 0; i < monsterInventory.size(); i++)
    {
        if(monsterInventory[i] == *objectMonster_)
        {
            found = true;
            monsterInventory[i] = *objectMonster_;
            break;
        }
    }


    if(found == false)
    {
        cout << "ERROR IN SWITCHING DUCKS" << endl;
    }
}

void Player::displayAllMonster()
{
    for(int i = 0; i < monsterInventory.size(); i++)
    {
        cout << "[" << i+ 1 << "]" << endl;
        cout << monsterInventory[i] << endl;
    }
}

Monster Player::selectMonster(int index_)
{
    return monsterInventory[index_];
}

void Player::monsterTagging()
{
    for(int i = 0; i < monsterInventory.size(); i++)
    {
        monsterInventory[i].setNumberTag(i);
    }
}
