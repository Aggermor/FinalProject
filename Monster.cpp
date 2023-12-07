#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Monster.hpp"

using namespace std;

// constructor
Monster::Monster()
{
    numberTag = 0;
    name = "NA";
    type = "NA";
    attack = 0;
    health = 0;
    MAX_HEALTH = 0;
}

Monster::Monster(string name_, string type_)
{
    numberTag = 0;
    name = name_;
    type = type_;

    if(type == "Water")
    {
        MAX_HEALTH = 175;
        health = 175;
        attack = 25;
        attack_name = {"Aqua Strike", "Splash", "Spray"};
    }
    else if(type == "Fire")
    {
        MAX_HEALTH = 100;
        health = 100;
        attack = 40;
        attack_name = {"Sear", "Flamethrower", "Torch"};
    }

    else if(type == "Wind")
    {
        MAX_HEALTH = 30;
        health = 30;
        attack = 95;
        attack_name = {"Breeze", "FeatherSlash", "Gust"};
    }
    else
    {
        cout << "error with Monster construction" << endl;
    }
}

// getters
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
    return MAX_HEALTH;
}



string Monster::getAttackName() const
{
    //srand(time(0));

    return attack_name[rand() % attack_name.size()];
}

// setters
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

// iostream overload
bool Monster::operator ==(const Monster& objectMonster_)
{
    return (this -> name == objectMonster_.getName() && this -> numberTag == objectMonster_.getNumberTag());
}
ostream& operator <<(ostream& out, const Monster& objectMonster_)
{

    out << "          Name: "<< objectMonster_.getName() << endl;
    out << "          Type: " <<  objectMonster_.getType() << "\n";
    out << "            HP: "<< objectMonster_.getHealth() << "/" << objectMonster_.getMAX_HEALTH() << "\n";
    out << "        Attack: "<< objectMonster_.getAttack() << "\n";

    return out;
}

