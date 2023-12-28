#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Monster.hpp"

using namespace std;

/*Define Monster Constructors and member functions/variables*/

//Constructor
Monster::Monster()
{
    numberTag = 0;
    name = "NA";
    type = "NA";
    attack = 0;
    health = 0;
    maxHealth = 0;
}

Monster::Monster(string name_, string type_)
{
    numberTag = 0;
    name = name_;
    type = type_;

    if(type == "Water")
    {
        maxHealth = 150;
        health = 150;
        attack = 25;
        attackName = {"Aqua Strike", "Splash", "Spray"};
    }
    else if(type == "Fire")
    {
        maxHealth = 100;
        health = 100;
        attack = 50;
        attackName = {"Sear", "Flamethrower", "Torch"};
    }

    else if(type == "Wind")
    {
        maxHealth = 75;
        health = 75;
        attack = 95;
        attackName = {"Breeze", "FeatherSlash", "Gust"};
    }
    else
    {
        cout << "MONSTER CONSTRUCTION ERROR!" << endl;
    }
}

//Getters
int Monster::getNumberTag() const
{
    return numberTag;

}

string Monster::getName() const
{
    return name;
}

string Monster::getType() const
{
    return type;
}

double Monster::getAttack() const
{
    return attack;
}

double Monster::getHealth() const
{
    return health;
}

double Monster::getMAX_HEALTH() const
{
    return maxHealth;
}

string Monster::getAttackName() const
{
    return attackName[rand() % attackName.size()]; //Randomizes attack names from vector of names
}

//Setters
void Monster::setNumberTag(int numberTag_)
{
    numberTag = numberTag_;
}

void Monster::setName(string name_)
{
    name = name_;
}

void Monster::setType(string type_)
{
    type = type_;
}

void Monster::setAttack(double attack_)
{
    attack = attack_;
}

void Monster::setHealth(double health_)
{
    health = health_;
}

/*Returns true (or false) by comparing the name and number tag of current monster object
(referenced by 'this') with the values of the objectMonster_*/
bool Monster::operator ==(const Monster& objectMonster_)
{
    return (this -> name == objectMonster_.getName() && this -> numberTag == objectMonster_.getNumberTag());
}

/*
this -> name and this -> numberTag access the name and numberTag of the current object
(the left-hand side of the equality). objectMonster_.getName()
 and objectMonster_.getNumberTag() access the corresponding values of the right-hand side.
*/

//Overloaded stream insertion operator that allows you to print the details of a monster to an output stream
ostream& operator <<(ostream& out, const Monster& objectMonster_)
{

    out << "          Name: "<< objectMonster_.getName() << endl;
    out << "          Type: " <<  objectMonster_.getType() << "\n";
    out << "            HP: "<< objectMonster_.getHealth() << "/" << objectMonster_.getMAX_HEALTH() << "\n";
    out << "        Attack: "<< objectMonster_.getAttack() << "\n";

    return out;
}

