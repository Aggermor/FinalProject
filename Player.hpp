#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

using namespace std;

class Player
{
protected:
    string name; //user chosen name
    vector<Monster> monsterInventory; //user Duckmon inventory
public:
    Player(); //default constructor
    Player(string name_); //constructor for player object

    string getName() const;
    vector<Monster> getMonsterInventory(); //returns vector of type Monster (player inventory)

    void setName(string name_);

    void monsterTagging();
    void updateMonsterInVector(Monster* objectMonster_); //for carryign data when switching
    void addMonster(Monster objectMonster_);
    void removeMonster(Monster objectMonster_);
    void displayAllMonster();
    Monster selectMonster(int index_);
    int getSize() const;
};

#endif // PLAYER_HPP_INCLUDED
