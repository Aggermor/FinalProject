#ifndef MONSTER_HPP_INCLUDED
#define MONSTER_HPP_INCLUDED

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Monster //Builds the Duckmon by defining their characteristics and behaviors in our RPG
{
private:
    int numberTag; //An identifier or tag for the monster
    string name; //The name of the monster
    string type; //The type (e.g., "Water", "Fire", "Wind") of the monster
    double attack; //The attack power of the monster
    double health; //The current health of the monster
    double maxHealth; //The maximum health the monster can have
    vector<string> attackName; //A vector containing names of different attacks the monster can perform

public:
    Monster(); //Default constructor initializing monster and member variables with default values
    Monster(string name_, string type_);
    /*Parameterized constructor that sets the name and type of the monster and initializes
    other attributes based on the monster's type*/

    /*
    Getters retrieve member variables for use in main or other functions
    Setters set member variables for modifications
    */

    int getNumberTag() const;
    void setNumberTag(int numberTag_);

    string getName() const;
    void setName(string name_);


    string getType() const;
    void setType(string type_);


    double getAttack() const;
    void setAttack(double attack_);


    double getHealth() const;
    void setHealth(double health_);


    double getMAX_HEALTH() const;

    string getAttackName() const; //Getter function to randomly retrieve attack name from vector attack_name


    //Overloaded equality operator to compare two monsters
    bool operator ==(const Monster& objectMonster_);

    //Overloaded stream insertion operator to print the monster's details to an output stream
    friend ostream& operator <<(ostream& out, const Monster& objectMonster_);
};

#endif

