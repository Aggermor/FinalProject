#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

using namespace std;

class Player
{
protected:
    string name;
    vector<Monster> monsterInventory;
public:
    // constructors
    Player();
    Player(string name_);

    //getters
    string getName() const;
    vector<Monster> getMonsterInventory();

    // setters
    void setName(string name_);

    // indexing
    void monsterTagging();
    void updateMonsterInVector(Monster* objectMonster_);
    void addMonster(Monster objectMonster_);
    void removeMonster(Monster objectMonster_);
    void displayAllMonster();
    Monster selectMonster(int index_);
    int getSize() const;


};

#endif // PLAYER_HPP_INCLUDED
