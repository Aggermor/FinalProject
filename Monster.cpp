#include <iostream>
#include <vector>
#include "Monster.hpp"


using namespace std;
/* Monster */

// constructor
Monster::Monster()
{
    name = "NA";
    type = "NA";
    attack = 0;
    health = 0;
    MAX_HEALTH = 0;
}

Monster::Monster(string name_, string type_)
{
    name = name_;
    type = type_;

    if(type == "Water")
    {
        MAX_HEALTH = 175;
        health = 175;
        attack = 25;
    }
    else if(type == "Fire")
    {
        MAX_HEALTH = 100;
        health = 100;
        attack = 40;
    }

    else if(type == "Wind")
    {
        MAX_HEALTH = 30;
        health = 30;
        attack = 95;
    }
    else
    {
        cout << "error with Monster construction" << endl;
    }
}

// getters
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

string Monster::getAttackName(Monster* objectMonster_)
{
    srand(time(0));
    int chance_ = rand() % 3;
    // test

    if(objectMonster_ -> getType() == "Fire")
    {
        string fireNames[3] = {" Sear", " Flamethrower", " Torch"};
        return fireNames[chance_];
    }
    else if(objectMonster_ -> getType() == "Water")
    {
        string waterNames[3] = {" Aqua Strike", " Splash", " Spray"};
        return waterNames[chance_];
    }
    else if (objectMonster_ -> getType() == "Wind")
    {
         string windNames[3] = { " Breeze", " FeatherSlash", " Gust" };
         return windNames[chance_];
    }
    else
    {
        return " Oops";
    }

}


// setters
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
    return (this -> name == objectMonster_.getName());
}
ostream& operator <<(ostream& out, const Monster& objectMonster_)
{

    out << "          Name: "<< objectMonster_.getName() << endl;
    out << "          Type: " <<  objectMonster_.getType() << "\n";
    out << "            HP: "<< objectMonster_.getHealth() << "/" << objectMonster_.getMAX_HEALTH() << "\n";
    out << "        Attack: "<< objectMonster_.getAttack() << "\n";

    return out;
}

