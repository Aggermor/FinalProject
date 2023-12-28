#include <iostream>
#include <vector>
#include "Monster.hpp"
#include "Player.hpp"

Player::Player()
{
    name = "NA";
}

Player::Player(string name_)
{
    name = name_;
}

string Player::getName() const
{
    return name;
}

vector<Monster> Player::getMonsterInventory()
{
    return monsterInventory; //returns user Duckmon inventory
}

int Player::getSize() const
{
    return monsterInventory.size(); //returns amount of Duckmon user has
}

void Player::setName(string name_)
{
    name = name_;
}

void Player::addMonster(Monster objectMonster_)
{
    monsterInventory.push_back(objectMonster_); //adds a Duckmon to player inventory
}

void Player::removeMonster(Monster objectMonster_) //removes Duckmon from inventory
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

void Player::updateMonsterInVector(Monster* objectMonster_) //for switching Duckmon and keeping stats the same after swtich
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

void Player::displayAllMonster() //displays user Duckmon inventory
{
    for(int i = 0; i < monsterInventory.size(); i++)
    {
        cout << "[" << i+ 1 << "]" << endl;
        cout << monsterInventory[i] << endl;
    }
}

Monster Player::selectMonster(int index_) //allows user to select a Duckmon
{
    return monsterInventory[index_];
}

void Player::monsterTagging() //assigns a number to each Duckmon for other uses
{
    for(int i = 0; i < monsterInventory.size(); i++)
    {
        monsterInventory[i].setNumberTag(i);
    }
}
